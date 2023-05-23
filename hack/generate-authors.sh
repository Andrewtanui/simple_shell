#!/bin/bash

contributors=$(git log --format='%aN <%aE>' | sort -fu)
authors_file="AUTHORS"
header="# CONTRIBUTORS\n\n"
content="${header}${contributors}"
echo -e "$content" > "$authors_file"
echo "AUTHORS file generated successfully."

