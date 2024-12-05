import os
import sys


def remove_extension(file):
    return file.split(".")[0]


def get_extension(file):
    return file.split(".")[-1]


def get_name(file):
    return file.split("/")[-1]


def get_files_in_dir(directory):
    # print(directory)
    files = []
    for file in os.listdir(directory):
        current_path = os.path.abspath(os.path.join(directory, file))
        if os.path.isfile(current_path):
            files.append(current_path)
        else:
            files.extend(get_files_in_dir(current_path))
    return files
