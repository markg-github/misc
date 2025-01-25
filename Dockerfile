
# Use a base image with Python and GCC
FROM python:3.9

# Set the working directory
WORKDIR /usr/src/app

RUN mkdir /usr/src/bin

COPY practice .

# RUN pip install --no-cache-dir -r requirements.txt

# Install GCC
RUN apt update && apt install -y gcc

# RUN gcc -g -o closest1 closest1.c
# RUN gcc -g -o countzeros countzeros.c
# RUN gcc -g -o fibonacci fibonacci.c
# RUN gcc -g -o find_primes find_primes.c
# RUN gcc -g -o invert_tree invert_tree.c
# RUN gcc -g -o is_balanced is_balanced.c
# RUN gcc -g -o ll_intersection ll_intersection.c

# give building a shot, but continue (|| true) regardless
RUN gcc -g -o /usr/src/bin/make_balanced make_balanced.c || true

# RUN gcc -g -o powerof2 powerof2.c
# RUN gcc -g -o tree_traversal tree_traversal.c
# RUN gcc -g -o twosum twosum.c

# Set the entry point to a shell
# ENTRYPOINT ["/bin/bash"]
