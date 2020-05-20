#include<iostream>
#include<vector>
/*
	Strategy pattern or a policy pattern is a pattern which enables us to select the algorithm at runtime.
	Instead of writing one main algorithm which handles the cases from if-else-if or switch, algorithm is
	selected at runtime from a family of instructions. 
	This allows us to decouple the algorithms and client code, makes code flexible and reusable. At any time
	we can come back to any algorithm and change it without changing client code.
	In this example, I have SortingStrategy which is an interface for Sorting strategies like Quick Sort,
	merge sort, heap sort etc. Sorter class uses the strategy pattern to select the strategy to sort the 
	give vector. This is because some particular sorting methods are good only for some cases and not all.
	You might still see if else in Sorter::sort() function. This can be totally avoided but I kept it as it is.
	Remember that strategy pattern has decoupled Sorter class from our algorithms. I can easily change the
	sorting strategy implementation without changing client code.
	Another example would be giving discounts, a special discount if amount of cart is more than some amount 
	else no discount. If some another new discount is added, say small discount if some particular item is
	in the cart, it can be done easily with strategy pattern.
	Not to mention that these strategies can be used anywhere else, in other strategy or other classes too!.
*/


class SortingStrategy
{
public:
	SortingStrategy(std::vector<int> arr) : arr(arr) {};
	std::vector<int> arr;
	virtual std::vector<int> sort() = 0;
};

class QuicKSort : public SortingStrategy
{
public:
	QuicKSort(std::vector<int> arr)
	: SortingStrategy(arr)
	{

	}
	std::vector<int> sort()
	{
		std::cout << "Sorting using quick sort!\n";
		// TODO: implement Quick Sort
		return arr;
	}
};

class MergeSort : public SortingStrategy
{
public:
	MergeSort(std::vector<int> arr)
	: SortingStrategy(arr)
	{

	}
	std::vector<int> sort()
	{
		std::cout << "Sorting using merge sort!\n";
		// TODO: implement merge sort
		return arr;
	}	
};

class HeapSort : public SortingStrategy
{
public:
	HeapSort(std::vector<int> arr)
	: SortingStrategy(arr)
	{

	}
	std::vector<int> sort()
	{
		std::cout << "Sorting using heap sort!\n";
		// implement Heap Sort
		return arr;
	}
};

class InsertionSort : public SortingStrategy
{
public:
	InsertionSort(std::vector<int> arr)
	: SortingStrategy(arr)
	{

	}
	std::vector<int> sort()
	{
		std::cout << "Sorting using insertion sort!\n";
		// TODO: implement Insertion Sort
		return arr;	
	}
};

class Sorter
{
private:
	std::vector<int> arr;
	SortingStrategy *s;
public:
	Sorter(std::vector<int> arr)
	: arr(arr)
	{
		
	}
	// large numbers to sort, need it stable, care about worst case performance
	std::vector<int> sort(bool large_n = true, bool stable = true, bool worst = false)
	{
		// if else if to be replaced by other mean
		if(!(stable || worst))
		{
			s = new QuicKSort(arr);
			return s->sort();
		} else if (stable && large_n) 
		{
			s = new MergeSort(arr);
			return s->sort();
		} else if (!large_n && stable && worst)
		{
			s = new InsertionSort(arr);
			return s->sort();
		} else if (!stable && worst && large_n)
		{
			s = new HeapSort(arr);
			return s->sort();
		} else 
		{
			std::cout << "Default!\n";
			s = new MergeSort(arr);
			return s->sort();
		}
	}
};

int main()
{
	std::vector<int> arr = {10, 5, 12, 7, 3, 10};
	Sorter *s = new Sorter(arr);
	s->sort(false, true, true); // should select insertion sort
	return 0;
}