// malloc_realloc.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include"Library.h"

//this class is needed in order to allocate memory in heap for convenience 
class buffer 
{
	void* buffer_complete;
public:
	buffer() = delete;
	buffer(const buffer&) = delete;
	buffer(buffer&&) = delete;
	buffer(size_t size, bool zero = false) 
	{
		if (zero)
				buffer_complete = calloc(1, sizeof(size));
		else
				buffer_complete = malloc(size);
		if (!buffer_complete)
				throw bad_alloc();
	}
	~buffer() 
	{
		free_buffer_complete();
	}
	buffer& operator=(const buffer&) = delete;
	buffer& operator=(buffer&&) noexcept=delete;
	void free_buffer_complete() 
	{
		if (buffer_complete)
		{
			free(buffer_complete);
			buffer_complete = nullptr;
		}
	}
	//
	void fill(int value,size_t size) 
	{
		if(buffer_complete)
		memset(buffer_complete, value, size);
	}
	bool resize(size_t size) 
	{
		void* lpbuff;
		if (buffer_complete)
			lpbuff= realloc(buffer_complete, size);
		if (!lpbuff)
			return false;
		buffer_complete = lpbuff;
		return true;
	}
	template<typename T>
	operator T*() const
	{
		return static_cast<T*>(buffer_complete);
	}

};
//
struct point 
{
	int x=0;
	int y=0;
};

int main()
{
//start

	point* p = (point *)malloc(sizeof(point)*10);
	if (p)
	{

	cout <<sizeof(p)<<endl;
	//memset(pointer,0 or -1,size pointer class)
	memset(p,0,sizeof(point));
	
	//or
	/*
	p->x = 1;
	p->y = 1;
	*/

	cout << "X: " << p->x << " | Y: " << p->y << endl; 
	
//end
	//let's free our pointer
	free(p);
	
	}
	/////////////////////////
	else 
	{
		// 
		if (errno == ENOMEM)
			cout << "ENOMEM" << endl;
		else
			cout << "Unknown" << endl;
 	}
	//satrt arr calloc
	int size = 10;
	point** arr = (point**)calloc(size, sizeof(point));
	if (arr) {
		memset(arr, 0, sizeof(point*));
		for (int i = 0; i < size; i++) {
			arr[i] = (point*)malloc(sizeof(point));
			
			arr[i]->x = i + 1;
			arr[i]->y = i + 2;
			//or memset(arr[i], 0, sizeof(point));
			
		}
		for (int i = 0; i < size; i++)
		{
			cout << "arr[" << i << "] = " << arr[i] << " | X: " << arr[i]->x << " Y: " << arr[i]->y << endl;
		}
		for (int i = 0; i < size; i++)
		//clear element arr
		free(arr[i]);
		//clear arr
		free(arr);
		
	}
	else 
	{
		// 
		if (errno == ENOMEM)
			cout << "ENOMEM" << endl;
		else
			cout << "Unknown" << endl;
	}
	//end arr calloc
	//
	//start calloc and realloc 
	point* Array = (point*)calloc(10,sizeof(point));
	if (Array) 
	{
		//realloc(copy Array,size and  class)
		point *newArray = (point*)realloc(Array,20*sizeof(point));
		if (newArray)
			Array = newArray;
		//(clear Array)
		free(Array);
	}
	else
	{
		if (errno == ENOMEM)
			cout << "ENOMEM" << endl;
		else
			cout << "Unknown" << endl;
	}
	//end calloc and realloc
	
//end
// start buffer 
	buffer buffer_(sizeof(point));
	point* po = buffer_;
	if (po) 
	{
		buffer_.fill(0, sizeof(point));
		//or
		po->x = 120;
		po->y = 321;
		cout << "po->x = " << po->x << " | po->y = " << po->y << endl;
		buffer_.free_buffer_complete();
	}
//end buffer
//start buffer arr
	buffer zbuffer(sizeof(point)*10,true);
	point *ps = zbuffer;
	if (ps) 
	{
		
		if (zbuffer.resize(20*sizeof(point))) 
		{
			ps = zbuffer;
		}
		for (int i=0;i<20;i++) 
		{
			arr[i]->x = i + 1;
			arr[i]->y = i + 2;
		}
		for (int i = 0; i < 20; i++) 
		{
			cout << "ps->x = " << ps->x << " | ps->y = " << ps->y << endl;
		}
		zbuffer.free_buffer_complete();
	}
	


//ens buffer arr
}
