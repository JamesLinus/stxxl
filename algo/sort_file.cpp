#include "../mng/mng.h"
#include "ksort.h"
#include "../containers/vector"

//! \example algo/sort_file.cpp 
//! This is an example of how to create \c stxxl::vector from an external file

using namespace stxxl;

struct my_type
{
	typedef unsigned key_type;
				
	key_type _key;
	char _data[128 - sizeof(key_type)];
	key_type key() const {return _key; };
							
	my_type() {};
	my_type(key_type __key):_key(__key) {};
									
	static my_type min_value(){ return my_type(0); };
	static my_type max_value(){ return my_type(0xffffffff); };
};

bool operator < (const my_type & a, const my_type & b)
{
	return a.key() < b.key();
}


int main()
{
		syscall_file f("./in",file::DIRECT|file::RDWR);
			
		unsigned memory_to_use = 512*1024*1024;
		typedef stxxl::vector<my_type> vector_type;
		vector_type v(&f);
	
	/*
		STXXL_MSG("Printing...")
		for(stxxl::int64 i=0; i < v.size(); i++)
			STXXL_MSG(v[i].key()); */
	
		STXXL_MSG("Checking order...")
		STXXL_MSG( ((stxxl::is_sorted(v.begin(),v.end()))?"OK":"WRONG" ));
	
		STXXL_MSG("Sorting...")
		stxxl::ksort(v.begin(),v.end(),memory_to_use);
	
		STXXL_MSG("Checking order...")
		STXXL_MSG( ((stxxl::is_sorted(v.begin(),v.end()))?"OK":"WRONG" ));
		
	
		return 0;
}
