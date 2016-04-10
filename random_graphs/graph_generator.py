#!/usr/bin/env python3
import random  # randint


def generate_graph(num_vertices, path):
    existing_edges = set()
    for i in range(1, num_vertices+1):
        i2 = random.randint(1, num_vertices)
        edge = (min(i, i2), max(i, i2))
        while i2 == i or edge in existing_edges:
            i2 = random.randint(1, num_vertices)
            edge = (min(i, i2), max(i, i2))
        existing_edges.add(edge)

    with open(path, 'w') as f:
        f.write('{verts} {edges}\n'.format(verts=num_vertices, edges=num_vertices))
        for edge1, edge2 in existing_edges:
            f.write('{} {}\n'.format(edge1, edge2))

for i in range(10**4, 10**6+1, 10**4):
    generate_graph(i, 'random_graph_{}.in'.format(i))
