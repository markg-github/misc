
# checkDuplicates.py


"""
Given a folder, walk through all files within the folder and subfolders
and get list of all files that are duplicates
The md5 checcksum for each file will determine the duplicates
"""

import os
import hashlib
from collections import defaultdict
import csv

import argparse
import logging, sys
import pdb


# src_folder = "../../"


def generate_md5(fname, chunk_size=1024):
    """
    Function which takes a file name and returns md5 checksum of the file
    """
    hash = hashlib.md5()
    with open(fname, "rb") as f:
        # Read the 1st block of the file
        chunk = f.read(chunk_size)
        # Keep reading the file until the end and update hash
        while chunk:
            hash.update(chunk)
            chunk = f.read(chunk_size)

    # Return the hex checksum
    return hash.hexdigest()


if __name__ == "__main__":
    """
    Starting block of script
    """

    pdb.set_trace()

    parser = argparse.ArgumentParser(description='Find duplicate files in a directory tree, given the directory')

    # Positional argument
    # parser.add_argument('posarg')

    # Optional argument
    parser.add_argument('--input_directory', type=str, help='directory', default="./")
    # temp_list = list(supported_processors.keys())
    # parser.add_argument('--processor', type=str, help='processor', default=temp_list[0], choices=temp_list)

    # parser.add_argument('-l', '--level', type=int, help='TCB levlel (0,1,2,...)', default=0)

    # Boolean flag
    # parser.add_argument('-v', '--verbose', action='store_true', help='Increase output verbosity')

    args = parser.parse_args()

    src_folder = args.input_directory

    # The dict will have a list as values
    md5_dict = defaultdict(list)

    file_types_inscope = ["ppt", "pptx", "pdf", "txt", "html",
                          "mp4", "jpg", "png", "xls", "xlsx", "xml",
                          "vsd", "py", "json"]

    # Walk through all files and folders within directory
    for path, dirs, files in os.walk(src_folder):
        print("Analyzing {}".format(path))
        for each_file in files:
            # if each_file.split(".")[-1].lower() in file_types_inscope:
            if True:
                # The path variable gets updated for each subfolder
                file_path = os.path.join(os.path.abspath(path), each_file)
                # If there are more files with same checksum append to list
                md5_dict[generate_md5(file_path)].append(file_path)

    # Identify keys (checksum) having more than one values (file names)
    duplicate_files = (
        val for key, val in md5_dict.items() if len(val) > 1)

    # Write the list of duplicate files to csv file
    with open("duplicates.csv", "w") as log:
        # Lineterminator added for windows as it inserts blank rows otherwise
        csv_writer = csv.writer(log, quoting=csv.QUOTE_MINIMAL, delimiter=",",
                                lineterminator="\n")
        header = ["File Names"]
        csv_writer.writerow(header)

        count = 0
        for file_name in duplicate_files:
            count += 1
            prefix = f"{count}: "
            prefixed_data = [prefix + str(item) for item in file_name]
            csv_writer.writerow(prefixed_data)

    print("Done")
