from PIL import Image
import numpy as np
import kmeans_algorithm as kmeans

class ImageCompressor:
    # Class constructor.
    # image_name - the name of the image to work with.
    def __init__(self, image_name):
        # Open the image and convert it to a NumPy array.
        # This array will be a 2D grid of pixels -> 3D array.
        print(f'Opening image {image_name}')
        image = Image.open(image_name)
        self.original_image = np.array(image)

        # Initialize the dictionary of compressed versions of the image.
        self.kmeans_images = {}

        # The current K-means value starts at 0.
        # This is the value used to know what K-means value to start on
        # when the image is reselected.
        self.current_k = 0
    
    # Return a compressed version of the image according to the current K-means value.
    def get_image(self):
        # For means=0, return the original image.
        # Otherwise, return the compressed version with the specified number of means.
        if self.current_k == 0:
            return self.original_image
        else:
            return self.kmeans_images[self.current_k]

    # Generate a new compressed version of the image.
    # k - the number of K-means clusters to use when compressing.
    def kmeans(self, k):
        # Set the cached K-means value now so that it's saved
        # even if the guard clauses return prematurely.
        self.current_k = k

        # We don't need to generate anything here. This is just the original image.
        if k == 0:
            return
        # The dictionary effectively acts as a cache for previously compressed images.
        # If the dictionary already has this value, don't bother trying to regenerate it.
        if k in self.kmeans_images:
            print(f'Already created compressed image with {k} means')
            return
        
        # Get the dimensions of the image.
        # We know the third value will be 3, for RGB pixels,
        # but the first two will be the height and with of the image.
        h, w, _ = self.original_image.shape
        # Flatten the 3D array (2D array of pixels) into a 2D array (1D array of pixels).
        # Now we just have a big array of RGB pixels.
        pixels = self.original_image.reshape(-1, 3)
        
        # Generate a K-means compressed version of the pixels.
        # Note that the return value will still be a 1D array of pixels.
        adjusted_pixels = kmeans.gen_kmeans_array_slow(pixels, k)
        
        # Reshape the 1D array according to the height and width parameters we got earlier.
        # In other words, shape the array of pixels into an actual image.
        # This is the array we save in the dictionary at the current K-means value.
        self.kmeans_images[k] = adjusted_pixels.reshape((h, w, 3))
        