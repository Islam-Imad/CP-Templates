import pypandoc
import os
import FilesUtility as fu


def convert_md_to_docx(input_file, output_file):
    if input_file is None:
        return
    pypandoc.convert_file(input_file, "docx", outputfile=output_file)


def create_md(input_file, output_path):
    input_file_extension = input_file.split(".")[-1]

    if input_file_extension == "docx":
        return

    input_file_name = input_file.split(".")[0]
    input_file_content = ""

    try:
        with open(input_file, "r") as f:
            input_file_content = f.read()
    except Exception as e:
        return

    output_file = input_file_name + "_" + input_file_extension + ".md"
    output_file = os.path.join(output_path, output_file)
    try:
        with open(output_file, "w") as f:
            if input_file_extension != "md":
                f.write(f"```{input_file_extension}\n")
            f.write(input_file_content)
            if input_file_extension != "md":
                f.write(f"\n```")
    except Exception as e:
        return
    return output_file
