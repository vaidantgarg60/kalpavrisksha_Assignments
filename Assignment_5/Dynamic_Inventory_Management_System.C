#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    int productId;
    char productName[50];
    float productPrice;
    int productQuantity;
} Product;

void addProduct(Product **inventory, int *totalProducts) {
    *totalProducts += 1;
    *inventory = (Product *)realloc(*inventory, (*totalProducts) * sizeof(Product));

    Product *newProduct = &((*inventory)[*totalProducts - 1]);
    printf("\nEnter new product details:\n");
    printf("Product ID: ");
    scanf("%d", &newProduct->productId);
    printf("Product Name: ");
    fgets(newProduct->productName, sizeof(newProduct->productName), stdin);
    newProduct->productName[strcspn(newProduct->productName, "\n")] = '\0';

    printf("Product Price: ");
    scanf("%f", &newProduct->productPrice);

    printf("Product Quantity: ");
    scanf("%d", &newProduct->productQuantity);

    printf("Product added successfully!\n");
}
void viewAllProducts(Product *inventory, int totalProducts) {
    if (totalProducts == 0) {
        printf("No products available.\n");
        return;
    }
    printf("\n PRODUCT LIST \n");
    for (int i = 0; i < totalProducts; i++) {
        printf("Product ID: %d | Name: %s | Price: %f | Quantity: %d\n",
               inventory[i].productId, inventory[i].productName,
               inventory[i].productPrice, inventory[i].productQuantity);
    }
}
void updateProductQuantity(Product *inventory, int totalProducts) {
    int productId;
    printf("Enter Product ID to update quantity: ");
    scanf("%d", &productId);

    for (int i = 0; i < totalProducts; i++) {
        if (inventory[i].productId == productId) {
            printf("Enter new Quantity: ");
            scanf("%d", &inventory[i].productQuantity);
            printf("Quantity updated successfully!\n");
            return;
        }
    }
    printf("Product not found!\n");
}

void searchProductById(Product *inventory, int totalProducts) {
    int productId;
    printf("Enter Product ID to search: ");
    scanf("%d", &productId);

    for (int i = 0; i < totalProducts; i++) {
        if (inventory[i].productId == productId) {
            printf("Product Found: Product ID: %d | Name: %s | Price: %f | Quantity: %d\n",
                   inventory[i].productId, inventory[i].productName,
                   inventory[i].productPrice, inventory[i].productQuantity);
            return;
        }
    }
    printf("Product not found!\n");
}

void searchProductByName(Product *inventory, int totalProducts) {
    char nameSearch[50];
    printf("Enter name to search (partial allowed): ");
    fgets(nameSearch, sizeof(nameSearch), stdin);

    bool productFound = false;
    printf("Products Found:\n");
    for (int i = 0; i < totalProducts; i++) {
        if (strstr(inventory[i].productName, nameSearch) != NULL) { // strcmp matches whole strinf not partt of it
            printf("Product ID: %d | Name: %s | Price: %f | Quantity: %d\n",
                   inventory[i].productId,inventory[i].productName,
                   inventory[i].productPrice, inventory[i].productQuantity);
            productFound = true;
        }
    }
    if (!productFound) {
        printf("No products found with given name.\n");
    }
}

void searchProductByPriceRange(Product *inventory, int totalProducts) {
    float minPrice, maxPrice;
    printf("Enter minimum price: ");
    scanf("%f", &minPrice);
    printf("Enter maximum price: ");
    scanf("%f", &maxPrice);

    bool found = false;
    printf("Products in price range:\n");
    for (int i = 0; i < totalProducts; i++) {
        if (inventory[i].productPrice >= minPrice && inventory[i].productPrice <= maxPrice) {
            printf("Product ID: %d | Name: %s | Price: %f | Quantity: %d\n",
                   inventory[i].productId, inventory[i].productName,
                   inventory[i].productPrice, inventory[i].productQuantity);
            found = true;
        }
    }
    if (!found) {
        printf("No products found in this price range.\n");
    }
}

void deleteProductById(Product **inventory, int *totalProducts) {
    int productId;
    printf("Enter Product ID to delete: ");
    scanf("%d", &productId);

    int index = -1;
    for (int i = 0; i < *totalProducts; i++) {
        if ((*inventory)[i].productId == productId) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Product not found!\n");
        return;
    }

    for (int i = index; i < (*totalProducts) - 1; i++) {
        (*inventory)[i] = (*inventory)[i + 1];
    }

    *totalProducts -= 1;
    *inventory = (Product *)realloc(*inventory, (*totalProducts) * sizeof(Product));

    printf("Product deleted successfully!\n");
}

int main() {
    int Ini_ProductCount;
    printf("Enter initial number of products: ");
    scanf("%d", &Ini_ProductCount);
    Product *inventory = (Product *)calloc(Ini_ProductCount, sizeof(Product));// i dont used malloc here becoz it does not initialize them to 0 

    for (int i = 0; i < Ini_ProductCount; i++) {
        printf("\nEnter details for product %d:\n", i + 1);
        printf("Product ID:");
         scanf("%d", &inventory[i].productId);

        printf("Product Name: ");
         fgets(inventory[i].productName, sizeof(inventory[i].productName), stdin);

        printf("Product Price: ");
        scanf("%f", &inventory[i].productPrice);

        printf("Product Quantity: ");
         scanf("%d", &inventory[i].productQuantity);
    }

    int userChoice;
    do {
        printf("\n       INVENTORY MENU          \n");
        printf("1. Add New Product\n");
        printf("2. View All Products\n");
        printf("3. Update Quantity\n");
        printf("4. Search Product by ID\n");
        printf("5. Search Product by Name\n");
        printf("6. Search Product by Price Range\n");
        printf("7. Delete Product\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &userChoice);

        switch (userChoice) {
            case 1:
                addProduct(&inventory, &Ini_ProductCount);
                break;
            case 2:
                viewAllProducts(inventory, Ini_ProductCount);
                break;
            case 3:
                updateProductQuantity(inventory, Ini_ProductCount);
                break;
            case 4:
                searchProductById(inventory, Ini_ProductCount);
                break;
            case 5:
                searchProductByName(inventory, Ini_ProductCount);
                break;
            case 6:
                searchProductByPriceRange(inventory, Ini_ProductCount);
                break;
            case 7:
                deleteProductById(&inventory, &Ini_ProductCount);
                break;
            case 8:
                printf("Memory released successfully. Exiting program...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }

    } while (userChoice != 8);
// i used do while loop here as i want to show menu once always so that user selexct options till termination in case 8
    free(inventory);
    return 0;
}
