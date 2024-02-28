
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void quickSort(int *arr, int low, int high) {
    if (low < high) {
        int leftPivot, rightPivot;

        if (arr[low] > arr[high]) {
            swap(&arr[low], &arr[high]);
        }

        leftPivot = arr[low];
        rightPivot = arr[high];

        int i = low + 1, k = low + 1, j = high - 1;

        while (k <= j) {
            if (arr[k] < leftPivot) {
                swap(&arr[i], &arr[k]);
                i++;
            } else if (arr[k] >= rightPivot) {
                while (arr[j] > rightPivot && k < j) {
                    j--;
                }

                swap(&arr[k], &arr[j]);
                j--;
                if (arr[k] < leftPivot) {
                    swap(&arr[i], &arr[k]);
                    i++;
                }
            }
            k++;
        }
        i--;
        j++;

        swap(&arr[low], &arr[i]);
        swap(&arr[high], &arr[j]);

        quickSort(arr, low, i - 1);
        quickSort(arr, i + 1, j - 1);
        quickSort(arr, j + 1, high);
    }
}


void selectionSort(int *arr, int len) {
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            if (arr[i] < arr[j])
            swap(&arr[i], &arr[j]);
        }
    }
}


void bubbleSort(int *arr, int len) {

    int swapped;
    for (int i = 0; i < len - 1; i++) {
        swapped = 0;
        for (int j = 0; j < len - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                swapped = 1;
            }
        }
        if (!(swapped))
        break;
    }
}