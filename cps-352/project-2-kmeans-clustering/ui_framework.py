import matplotlib
from matplotlib.widgets import Slider, Button
from image_compressor import ImageCompressor
from typing import List
# This part was necessary to get things running on Windows.
# It was suggested by ChatGPT.
matplotlib.use('TkAgg')
import matplotlib.pyplot as plt


# List of image filenames. This is constant.
IMAGE_FILE_NAMES = ["images/test1.jpg", 
                    "images/test2.jpg"]

# Create a list of image compressor objects, one for each image in the list.
image_compressor_list: List[ImageCompressor] = []
for image_name in IMAGE_FILE_NAMES:
    image_compressor_list.append(ImageCompressor(image_name))

# Start the application by loading the first image in the list.
current_image_index = 0


# Create the initial plot with the first image in the list.
fig, ax = plt.subplots(figsize=(8, 5))
plt.subplots_adjust(bottom=0.3)  # Adjust space for buttons and slider
ax.set_title("K-Means Clustering")
ax.axis('off')
# Display the initial image
img_display = ax.imshow(image_compressor_list[current_image_index].get_image())
# Add a slider for brightness control
ax_slider = plt.axes([0.25, 0.1, 0.5, 0.03])  # x, y, width, height
slider = Slider(ax_slider, 'Clusters', 0, 64, valinit=0, valstep=1)


# This is the callback for any slider movements.
# means - the current value of the slider.
def update(means):
    # Generate a new compressed version of the image.
    image_compressor_list[current_image_index].kmeans(means)
    # Update the displayed image.
    img_display.set_data(image_compressor_list[current_image_index].get_image())
    # Redraw the canvas in the app.
    fig.canvas.draw_idle()

# This is the callback for "Prev" and "Next" button presses.
# When a button is pressed, a new image from the list will be displayed.
# direction - which way to step in the list for the new image.
#       "Next" to get the image at current_index + 1
#       "Prev" to get the image at current_index - 1
def change_image(direction):
    global current_image_index
    if direction == 'next':
        # Move to the next image, wrapping around if necessary.
        current_image_index = (current_image_index + 1) % len(IMAGE_FILE_NAMES)
    elif direction == 'prev':
        # Move to the previous image, wrapping around if necessary.
        current_image_index = (current_image_index - 1) % len(IMAGE_FILE_NAMES)

    # Set the value of the slider to the cached value in the image compressor object.
    slider.set_val(image_compressor_list[current_image_index].current_k)
    # Update the displayed image.
    img_display.set_data(image_compressor_list[current_image_index].get_image())
    # Redraw the canvas in the app.
    fig.canvas.draw_idle()


def main():
    # Create "Previous" and "Next" buttons.
    ax_prev = plt.axes([0.1, 0.01, 0.1, 0.075]) # x, y, width, height
    ax_next = plt.axes([0.8, 0.01, 0.1, 0.075])
    button_prev = Button(ax_prev, 'Previous')
    button_next = Button(ax_next, 'Next')

    # Init the button callbacks.
    button_prev.on_clicked(lambda event: change_image('prev'))
    button_next.on_clicked(lambda event: change_image('next'))
    # Init the slider callback.
    slider.on_changed(lambda event: update(slider.val))

    # Finally, display the plot.
    plt.show()


if __name__ == "__main__":
    main()
