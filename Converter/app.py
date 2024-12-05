import os

import Converter
import FilesUtility as fu

input_path = input("Enter the path where your files reside in : ").strip()
while not os.path.exists(input_path):
    print("Invalid path")
    input_path = input("Enter the path where your files reside in : ").strip()
    continue
input_path = os.path.abspath(input_path)

output_path = input(
    "Enter the path where you want to save the converted files : "
).strip()
while not os.path.exists(output_path):
    print("Invalid path")
    output_path = input(
        "Enter the path where you want to save the converted files : "
    ).strip()
    continue
output_path = os.path.abspath(output_path)

files = fu.get_files_in_dir(input_path)

for file in files:
    docx_file_path = os.path.join(
        output_path, fu.remove_extension(fu.get_name(file)) + "_" + fu.get_extension(file) + ".docx"
    )
    md_file_path = Converter.create_md(file, output_path)
    Converter.convert_md_to_docx(md_file_path, docx_file_path)
    if md_file_path:
        os.remove(md_file_path)
