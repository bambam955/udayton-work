from PIL import Image

class ImageCompressor:
    def __init__(self, image_name):
        print(f'Opening image {image_name}')
        self.original_image = Image.open(image_name)
        self.kmeans_images = []
    
    def kmeans(self, num):
        self.kmeans_images[num] = self.original_image

    def get_image(self, k):
        if k == 0:
            return self.original_image
        else:
            return self.kmeans_images[k]
        