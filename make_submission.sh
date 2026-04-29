#!/bin/bash
set -e

OUT=dist
STAGE="$OUT/staging"
rm -rf "$STAGE" "$OUT"/cppgraph_source.zip
mkdir -p "$STAGE"

# Pre-flight: compiled .cpp files must include memtrace.h
for f in src/main.cpp src/playground.cpp test/main.cpp; do
    if ! grep -q '#include "memtrace.h"' "$f"; then
        echo "ERROR: $f missing #include \"memtrace.h\"" >&2
        exit 1
    fi
done

# Pre-flight: no relative ../ includes left
if grep -rn '#include[[:space:]]*"\.\./' src test; then
    echo "ERROR: relative '../' includes present — flat ZIP needs path-less includes" >&2
    exit 1
fi

# Stage flat: program headers + test headers + test main as main.cpp
cp src/graph.h src/array.h src/node.h src/persistable.h src/pint.h "$STAGE/"
cp test/array_test.h test/node_test.h test/graph_test.h "$STAGE/"
cp test/main.cpp "$STAGE/main.cpp"

# ZIP from inside staging so paths are bare
( cd "$STAGE" && zip "../cppgraph_source.zip" * )
rm -rf "$STAGE"

echo "Submission ZIP ready: $OUT/cppgraph_source.zip"
