# """https://graphviz.org/Gallery/directed/hello.html"""

# import graphviz

# g = graphviz.Digraph('G', filename='hello.gv')

# g.edge('Hello', 'World')

# g.view()
import pygraphviz as pgv
G = pgv.AGraph()
G.add_node("a")
G.add_edge("b", "c")

print(G)
G.write("file.dot")

G.layout() # default to neato
G.layout(prog='dot') # use dot
G.draw('file.png')  # write previously positioned graph to PNG file
G.draw('file.ps',prog='circo') # 