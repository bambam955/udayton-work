import numpy as np


def gen_kmeans_array(data, kmeans, max_iterations=10, threshold=0.1):
    adjusted = data.copy()
    # initialize centroid
    centers = np.random.randint(0, 255, (kmeans, 3))
    print(centers)

    # Start K-mean repeating process
    for iteration in range(max_iterations):
        groups = [[]  for _ in range(kmeans)]
        labels = []

        print(f'************* iteration [{iteration + 1}] ***************')
        # 1 traverse each number and calculate its distance to each
        # centroid and pick the smaller one as group assignment
        distances = np.linalg.norm(adjusted[:, np.newaxis, :] - centers[np.newaxis, :, :], axis=2)
        labels = np.argmin(distances, axis=1)
            
        # 2 Re-compute the new centroid
        centers_new = np.zeros_like(centers)
        for i in range(kmeans):
            mask = (labels == i)
            if np.any(mask):
                centers_new[i] = np.mean(adjusted[mask], axis=0)
            else:
                centers_new[i] = centers[i]  # Keep old center if cluster is empty
        
        # check if the centers get stable
        is_stable_now = True
        for i in range(len(centers_new)):
            if abs(np.linalg.norm(centers[i] - centers_new[i])) / np.linalg.norm(centers[i]) >= threshold:
                is_stable_now = False
        
        if is_stable_now:
            break

        centers = centers_new
            
    for i in range(adjusted.shape[0]):
        adjusted[i] = centers[labels[i]]

    print(f'FINAL CENTERS: {centers}')

    return adjusted
