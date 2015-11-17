#!/bin/sh

echo Updating everything &&
git pull && 
git submodule foreach git submodule update --recursive --remote