from PIL import Image
import numpy as np

class ImageCompressor:
    def __init__(self, image_name):
        print(f'Opening image {image_name}')
        image = Image.open(image_name)
        self.original_image = np.array(image) / 255.0 # Normalize to range [0, 1]
        self.kmeans_images = {}
    
    def kmeans(self, num):
        self.kmeans_images[num] = self.original_image

    def get_image(self, k):
        if k == 0:
            return self.original_image
        else:
            return self.kmeans_images[k]
        