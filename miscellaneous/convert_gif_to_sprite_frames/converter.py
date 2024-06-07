from PIL import Image, ImageSequence
import os
import math

def image_grid(imgs, rows, cols):
    #assert len(imgs) == rows*cols

    w, h = imgs[0].size
    grid = Image.new('RGB', size=(cols*w, rows*h))
    grid_w, grid_h = grid.size
    
    for i, img in enumerate(imgs):
        grid.paste(img, box=(i%cols*w, i//cols*h))
    return grid

for file in os.listdir('.'):
    if file.endswith('.gif'):
        img = Image.open(file)

        frames = []
        index = 1
        for frame in ImageSequence.Iterator(img):
            frames.append(frame)
            index += 1

        n_rows = int(math.ceil(math.sqrt(len(frames))))
        n_cols = int(math.ceil(len(frames) / n_rows))

        grid = image_grid(frames, n_rows, n_cols)

        grid.save(file.replace('.gif', '.png'))