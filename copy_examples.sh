#!/bin/bash

if [ $# -eq 0 ]; then
  echo "No arguments supplied"
  exit 1
fi

if [ "$#" -ne 1 ]; then
  echo "Illegal number of parameters"
  exit 1
fi

if [[ "$1" == "alice" ]]; 
then
  rm -rf data/*
  rm -rf src/config/*
  
  cp examples/alice/agentspeak.asl data/
  cp examples/alice/functions.* data/
fi

if [[ "$1" == "bob" ]];
then
  rm -rf main/data/*
  rm -rf main/src/config/*

  cp examples/bob/agentspeak.asl data/
  cp examples/bob/functions.* data/
fi
