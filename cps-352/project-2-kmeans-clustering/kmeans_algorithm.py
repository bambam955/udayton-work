import numpy as np

# Generate an compressed version of the given NumPy array of pixels
# based on the K-means clustering algorithm.
# data - the array of pixels to compress.
# kmeans - the number of clusters to use.
# max_iterations - The maximum amount of times to regenerate the clusters.
#       This argument is provided to cap the runtime of the algorithm.
# threshold - the centroid shift percentage at which the clusters
#       will be considered stable.
def gen_kmeans_array(data, kmeans, max_iterations=10, threshold=0.1):
    # Copy the data so we don't edit the original.
    adjusted = data.copy()

    # Initialize the centroids. These are random pixels.
    # We need one centroid for each cluster/mean.
    centroids = np.random.randint(0, 255, (kmeans, 3))
    np.random.seed(1234)

    # Start the K-means algorithm.
    # The basic idea is to keep refining the centroids until
    # they are the best possible representation of the image.
    for iteration in range(max_iterations):
        # print(f'************* iteration [{iteration + 1}] ***************')
        
        # This will be a list storing the centroid each pixel is assigned to.
        # We'll use this 
        labels = []

        # 1. For each pixel, calculate its Euclidean distance to each centroid.
        #    The smallest distance will determine the pixel's cluster assignment.
        
        # Add a new dimension to the array of pixels and to the array of centroids.
        # This allows them to be easily compared by subtraction.
        pixels_expanded = adjusted[:, np.newaxis, :]  # (N, 1, 3)
        centers_expanded = centroids[np.newaxis, :, :]  # (1, K, 3)
        diffs = pixels_expanded - centers_expanded    # (N, K, 3)
        distances = np.linalg.norm(diffs, axis=2)     # (N, K)
        # Assign the label as the index of the smallest distance.
        labels = np.argmin(distances, axis=1)
        
        # 2. Generate a list of new centroids by computing the mean
        #    of each cluster and assigning that as the new centroid.

        # Initialize a list of zeroes the same size as the list of centers.
        centers_new = np.zeros_like(centroids)
        for i in range(kmeans):
            # Generate an array of booleans, the same length as the list of pixels,
            # where each value is either True for a pixel in the cluster or False
            # for a pixel that isn't in the cluster.
            mask = (labels == i)
            # Are there any elements in the cluster? If so, compute the mean.
            # If not, don't even bother regenerating the centroid.
            if np.any(mask):
                # adjusted[mask] will return an array of all pixels in the cluster.
                centers_new[i] = np.mean(adjusted[mask], axis=0)
            else:
                # Keep old center if cluster is empty.
                centers_new[i] = centroids[i]
        
        # 3. See if the centroids have stabilized yet. The centroids are stable
        #    if the change from last regeneration to this one is below the threshold percentage.
        
        # Start off as true, then see if any new centroids are unstable.
        is_stable_now = True
        for i in range(len(centers_new)):
            # If any one of the centroids changes by more than the threshold, then
            # the centroids are not stable yet.
            if abs(np.linalg.norm(centroids[i] - centers_new[i])) / np.linalg.norm(centroids[i]) >= threshold:
                is_stable_now = False
        
        # If the centroids are stable, we don't need to iterate again. Break out of the loop.
        if is_stable_now:
            break

        # Set the list of centroids to the regenerated centroids
        # in preparation for the next iteration.
        centroids = centers_new

    # 4. Generate the compressed list of pixels from the list of cluster labels.
    #    Each pixel in the adjusted data will now be the centroid of its cluster.  
    for i in range(adjusted.shape[0]):
        adjusted[i] = centroids[labels[i]]

    # Return the compressed pixels.
    return adjusted
