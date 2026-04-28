#!/bin/bash
set -e

# Generate API docs from source
doxide build

# Copy specification and assets into doxide output
cp docs/specification.md doxide/
cp docs/documentation.md doxide/
cp -r docs/uml-diagram doxide/

# Build the site
mkdocs build
