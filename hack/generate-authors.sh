#!/bin/bash

contributors=$(git log --format='%aN <%aE>' | sort -fu)
authors_file="AUTHORS"
echo "$contributors" > "$authors_file"
echo "AUTHORS file generated successfully."

