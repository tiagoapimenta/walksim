#!/bin/bash

if [ $# -lt 1 ]; then
	echo "Nenhuma classe criada." >&2
	exit 1
fi

for cla in "$@"; do
	lcla=$(echo "$cla" | tr '[:upper:]' '[:lower:]')
	ucla=$(echo "$cla" | tr '[:lower:]' '[:upper:]')
	if [ "$cla" == "$lcla" -o "$cla" == "$ucla" ]; then
		echo "Classe \"$cla\" sem variação de tramanho de letra." >&2
		continue
	fi
	if [ -e "${lcla}.h" ]; then
		echo "Arquivo \"${lcla}.h\" já existe." >&2
		continue
	fi
	if [ -e "${lcla}.cpp" ]; then
		echo "Arquivo \"${lcla}.cpp\" já existe." >&2
		continue
	fi
	echo -e "#ifndef ${ucla}_H\n#define ${ucla}_H\n\nclass ${cla}\n{\nprivate:\n\npublic:\n\t${cla}();\n};\n\n#endif" > "${lcla}.h"
	echo -e "#include \"${lcla}.h\"\n\n${cla}::${cla}()\n{\n}" > "${lcla}.cpp"
done
