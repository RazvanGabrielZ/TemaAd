import sys
import math

MAX_BOOKS = 100

def print_employee_books(books, allocation, num_books, employee_name):
    print(f"{employee_name}: ", end="")
    first = True
    for i in range(num_books):
        if allocation[i]:
            if not first:
                print(", ", end="")
            print(f"Book {i + 1} ({books[i]} pages)", end="")
            first = False
    print()

def print_distribution(books, num_books, allocation_emp1, allocation_emp2, allocation_emp3):
    print("\nDistribution of books:")
    print_employee_books(books, allocation_emp1, num_books, "Employee 1")
    print_employee_books(books, allocation_emp2, num_books, "Employee 2")
    print_employee_books(books, allocation_emp3, num_books, "Employee 3")

def find_best_distribution(books, num_books):
    total_sum = sum(books)

    best_max_diff = math.inf  # Initialize with the largest possible integer to ensure any first found value is smaller.
    best_allocation_emp1 = [0] * MAX_BOOKS
    best_allocation_emp2 = [0] * MAX_BOOKS
    best_allocation_emp3 = [0] * MAX_BOOKS

    # Start bitmask from 1 to ensure at least one book is assigned to each employee
    for mask1 in range(1, 1 << num_books):
        for mask2 in range(1, 1 << num_books):
            # Ensure each mask is unique and they cover all books
            mask3 = ((1 << num_books) - 1) & ~(mask1 | mask2)
            if not mask3 or (mask1 & mask2) or (mask1 & mask3) or (mask2 & mask3):
                continue  # Skip invalid or overlapping combinations.

            allocation_emp1 = [0] * MAX_BOOKS
            allocation_emp2 = [0] * MAX_BOOKS
            allocation_emp3 = [0] * MAX_BOOKS
            pages_emp1 = 0
            pages_emp2 = 0
            pages_emp3 = 0

            for book in range(num_books):
                if mask1 & (1 << book):
                    pages_emp1 += books[book]
                    allocation_emp1[book] = 1
                if mask2 & (1 << book):
                    pages_emp2 += books[book]
                    allocation_emp2[book] = 1
                if mask3 & (1 << book):
                    pages_emp3 += books[book]
                    allocation_emp3[book] = 1

            max_pages = max(pages_emp1, pages_emp2, pages_emp3)

            if max_pages < best_max_diff:
                best_max_diff = max_pages
                best_allocation_emp1 = allocation_emp1[:]
                best_allocation_emp2 = allocation_emp2[:]
                best_allocation_emp3 = allocation_emp3[:]

    print_distribution(books, num_books, best_allocation_emp1, best_allocation_emp2, best_allocation_emp3)

def main():
    num_books = int(input("Enter number of books (up to 100): "))

    if num_books <= 0 or num_books > MAX_BOOKS or num_books < 3:
        print("Invalid number of books, press any key to exit...")
        input()
        return

    books = []
    print("Enter number of pages in each book:")
    for i in range(num_books):
        books.append(int(input(f"Book {i + 1}: ")))

    find_best_distribution(books, num_books)

    print("\nPress any key to exit...")
    input()

if __name__ == "__main__":
    main()
