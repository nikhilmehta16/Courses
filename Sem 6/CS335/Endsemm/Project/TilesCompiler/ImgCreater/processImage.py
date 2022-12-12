'''
Converts the output of tiles program to an actual image.
How to run:
       python3 ImgCreator.py <input> [<output>.png]

Input: A file containing pattern specification.
       First Line: row, column
       next "row" lines: [tile1, tile2, ..., tile_col]
Output: A png file (Default: 'NewImage.png'

NOTE: A very simple python script. No error handling.

'''

from PIL import Image
import sys

# Open images and store them in a list
a0,a1,a2,a3 = 'a0','a1','a2','a3'
b0,b1,b2,b3 = 'b0','b1','b2','b3'
images = {x:Image.open(x + '.png') for x in [a0, a1, a2, a3, b0, b1, b2, b3]}

Tiles=open(sys.argv[1], 'r')
OutFile='NewImage.png'
if (len(sys.argv) == 3):
    OutFile = sys.argv[2]

# find the width and height of the final image
# rows, cols given in the first line of the tiles file.
dimensions = Tiles.readline()
rows, cols = eval(dimensions)
img_width = images[a0].size[0]
img_height = images[a0].size[1]
total_width = cols * img_width
total_height = rows *img_height

# create a new image with the appropriate height and width

new_img = Image.new('RGB', (total_width, total_height))

current_height = 0
for row in Tiles:
    rw = eval(row)
    print(rw)
    # Write the contents of the new image
    current_width = 0
    for imgID in rw:
        img = images[imgID]
        new_img.paste(img, (current_width,current_height))
        current_width += img_width
    current_height += img_height

# Save the image
new_img.save(OutFile)

