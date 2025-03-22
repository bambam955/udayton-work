from PIL import Image
import numpy as np

class ImageCompressor:
    def __init__(self, image_name):
        print(f'Opening image {image_name}')
        image = Image.open(image_name)
        self.original_image = np.array(image) / 255.0 # Normalize to range [0, 1]
        self.kmeans_images = {}
        self.current_k = 0
    
    def kmeans(self, num):
        if num in self.kmeans_images:
            print(f'Already created compressed image with {num} means')
            return
        # TODO: k-means compress algorithm
        adjusted_image = np.clip(self.original_image * num, 0, 1)  # Keep values in range [0, 1]
        self.kmeans_images[num] = adjusted_image
        self.current_k = num

    def get_image(self):
        if self.current_k == 0:
            return self.original_image
        else:
            return self.kmeans_images[self.current_k]
        