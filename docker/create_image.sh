#!/bin/bash

# Configurações
DOCKER_USER=maiquelb
DOCKER_REPO=embedded-bdi

# Solicita a versão ao usuário
read -p "Digite a versão da imagem (exemplo: 1.0): " VERSION
IMAGE_NAME="$DOCKER_USER/$DOCKER_REPO"

# Build da imagem com a versão informada e com tag latest
echo "🔨 Construindo a imagem Docker..."
docker build -t $IMAGE_NAME:$VERSION .
docker tag $IMAGE_NAME:$VERSION $IMAGE_NAME:latest

# Login no Docker Hub (caso não esteja logado)
docker login

# Obtém o digest da imagem latest antiga
TOKEN=$(curl -s -H "Content-Type: application/json" -X POST -d '{"username": "'$DOCKER_USER'", "password": "'$(cat ~/.docker/config.json | jq -r .auths["https://index.docker.io/v1/"].auth | base64 -d | cut -d: -f2)'"}' https://hub.docker.com/v2/users/login/ | jq -r .token)
DIGEST=$(curl -s -H "Authorization: Bearer $TOKEN" "https://hub.docker.com/v2/repositories/$DOCKER_USER/$DOCKER_REPO/tags/latest" | jq -r '.images[0].digest')

# Apaga a tag latest antiga se existir
if [ "$DIGEST" != "null" ]; then
    echo "🗑️ Removendo imagem latest antiga..."
    curl -s -X DELETE -H "Authorization: Bearer $TOKEN" "https://hub.docker.com/v2/repositories/$DOCKER_USER/$DOCKER_REPO/tags/latest"
fi

# Faz push das imagens
echo "📤 Enviando as imagens para o Docker Hub..."
docker push $IMAGE_NAME:$VERSION
docker push $IMAGE_NAME:latest

echo "✅ Push concluído com sucesso!"

