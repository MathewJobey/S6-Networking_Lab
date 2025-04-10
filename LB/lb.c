#include<stdio.h>

int main() {
    // Declare variables
    int bucket_size, bucket, out_rate, n;

    bucket = 0;  // Initially,the bucket is empty

    // Input the max size of the bucket
    printf("Bucket size: ");
    scanf("%d", &bucket_size);

    // Input the fixed outflow rate
    printf("Outflow rate: ");
    scanf("%d", &out_rate);

    // Input the number of incoming packets (how many times loop will run)
    printf("No. of incoming packets: ");
    scanf("%d", &n);

    int _in;  // Variable to store each incoming packet size

    // Loop to process each incoming packet
    for (int i = 0; i < n; i++) {
        // Take the incoming packet size as input
        printf("\n\nIncoming packet: ");
        scanf("%d", &_in);

        // Check if packet fits in the bucket
        if (_in <= (bucket_size - bucket)) {
            // Add packet to the bucket
            bucket = bucket + _in;
            printf("Adding Packet: %d/%d", bucket, bucket_size);
        } else {
            // If not enough space, drop the extra part
            printf("Dropped %d", _in - (bucket_size - bucket));
            bucket = bucket_size;  // Bucket is now full
        }

        // Leak packets at a constant rate (outflow)
        if (bucket - out_rate > 0) {
            bucket = bucket - out_rate;  // Reduce bucket by outflow rate
        } else {
            bucket = 0;  // If not enough data to leak, empty the bucket
        }

        // Print the status of the bucket after each operation
        printf(" | STATUS -> Bucket Filled: %d/%d", bucket, bucket_size);
    }

    return 0;
}
