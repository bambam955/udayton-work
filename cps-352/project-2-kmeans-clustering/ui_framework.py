from PIL import Image
import matplotlib
matplotlib.use('TkAgg')
import matplotlib.pyplot as plt
import numpy as np
from matplotlib.widgets import Slider, Button
from image_compressor import ImageCompressor
from typing import List

# List of image filenames
image_filenames = ["images/test1.jpg", "images/test2.jpg"]
image_compressor_list: List[ImageCompressor] = []
for i in range(len(image_filenames)):
    image_compressor_list.append(ImageCompressor(image_filenames[i]))

# Load the initial image
current_image_index = 0

# Create the initial plot
fig, ax = plt.subplots(figsize=(8, 5))
plt.subplots_adjust(bottom=0.3)  # Adjust space for buttons and slider
ax.set_title("K-Means Clustering")
ax.axis('off')

# Display the initial image
img_display = ax.imshow(image_compressor_list[current_image_index].get_image())

# Add a slider for brightness control
ax_slider = plt.axes([0.25, 0.1, 0.5, 0.03])  # x, y, width, height
slider = Slider(ax_slider, 'Clusters', 0, 64, valinit=0, valstep=1)


# Update function for slider
def update(means):
    # Scale the brightness of the image
    image_compressor_list[current_image_index].kmeans(means)
    img_display.set_data(image_compressor_list[current_image_index].get_image())  # Update the displayed image
    fig.canvas.draw_idle()  # Redraw the canvas

# Function to load and display the next/previous image
def change_image(direction):
    global current_image_index
    if direction == 'next':
        # Move to the next image, wrapping around if necessary
        current_image_index = (current_image_index + 1) % len(image_filenames)
    elif direction == 'prev':
        # Move to the previous image, wrapping around if necessary
        current_image_index = (current_image_index - 1) % len(image_filenames)

    # Load the new image and update the display
    slider.set_val(image_compressor_list[current_image_index].current_k)
    img_display.set_data(image_compressor_list[current_image_index].get_image())  # Update the displayed image
    fig.canvas.draw_idle()  # Redraw the canvas

def main():
    # Add "Previous" and "Next" buttons
    ax_prev = plt.axes([0.1, 0.01, 0.1, 0.075])  # x, y, width, height
    ax_next = plt.axes([0.8, 0.01, 0.1, 0.075])

    button_prev = Button(ax_prev, 'Previous')
    button_next = Button(ax_next, 'Next')

    # Define the button callbacks
    button_prev.on_clicked(lambda event: change_image('prev'))
    button_next.on_clicked(lambda event: change_image('next'))

    # Connect the slider to the update function
    slider.on_changed(lambda event: update(slider.val))

    # Show the plot
    plt.show()

if __name__ == "__main__":
    main()
