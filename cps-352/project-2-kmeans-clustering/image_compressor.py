from PIL import Image
import numpy as np
from numpy import random as rand
import kmeans_algorithm as kmeans

class ImageCompressor:
    def __init__(self, image_name):
        print(f'Opening image {image_name}')
        image = Image.open(image_name)
        self.original_image = np.array(image) # Normalize to range [0, 1]
        self.kmeans_images = {}
        self.current_k = 0
        rand.seed(5) # fix our random generation
    
    def get_image(self):
        if self.current_k == 0:
            return self.original_image
        else:
            return self.kmeans_images[self.current_k]

    def kmeans(self, k):
        self.current_k = k
        if k == 0:
            return
        if k in self.kmeans_images:
            print(f'Already created compressed image with {k} means')
            return
        
        h, w, _ = self.original_image.shape
        # Reshape into (num_pixels, 3)
        pixels = self.original_image.reshape(-1, 3)
        
        adjusted_pixels = kmeans.gen_kmeans_array(pixels, k)
        
        self.kmeans_images[k] = adjusted_pixels.reshape((h, w, 3))

        