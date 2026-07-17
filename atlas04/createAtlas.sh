#!/bin/bash -e

cd dev

../gen04 -dir gfx

mv atlas.png ../gfx/
mv atlas.json ../data/
