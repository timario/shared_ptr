//////// For use of testing need add manager of configuration and add directive of preprocessor  ///////
///////  File for testing catch.hpp in folder catch2/catch.hpp
/////// Project in http://git.fondbozori.uz/developers/sandbox/latfullin_timur/shared-ptr/-/tree/develop  /////

#ifdef TESTING
#define CATCH_CONFIG_MAIN

#include "catch2/catch.hpp"
#include "shared.h"



TEST_CASE("TESTING VALUES & CONSTRUCTOR")
{
	int* a = new int(5);
	shared_ptr<int> _f_pt(a);
	shared_ptr<int> _f_pt2(_f_pt);
	shared_ptr<int> _f_pt3(new int);
	*_f_pt3 = *_f_pt2;
	std::shared_ptr<int> f_pt_(a);
	REQUIRE(*_f_pt == *f_pt_);
	REQUIRE(*_f_pt.get() == *f_pt_.get());
	
	REQUIRE(*_f_pt == *f_pt_);  ////TEST of constructor with ptr
	REQUIRE(*_f_pt2 == *f_pt_); ////TEST of constructor with other object this class
	REQUIRE(*_f_pt3 == *f_pt_); ////TEST of constructor with nullptr and after assignment values


	*f_pt_ = 10;
}

TEST_CASE("TESTING OPERATOR")
{
	std::string* a = new std::string("asd");
	std::string* new_str = new std::string("qwe");
	shared_ptr<std::string> _f_pt(a);
	shared_ptr<std::string> _f_pt2(_f_pt);
	std::shared_ptr<std::string> f_pt_(a);
	std::shared_ptr<std::string> f_pt_2(f_pt_);

	REQUIRE(_f_pt->size() == f_pt_->size());
	REQUIRE(*_f_pt == *f_pt_);

	_f_pt2.reset(new_str);
	f_pt_2.reset(new_str);

	REQUIRE(*_f_pt2 == "qwe");

	_f_pt = _f_pt2;

	REQUIRE(*_f_pt == "qwe");

	REQUIRE((_f_pt));
	
	_f_pt.reset();
	REQUIRE(!(_f_pt));

}
//
TEST_CASE("COUNT & UNIQUE TESTING & SWAP")
{
	std::string* a = new std::string("asd");
	std::string* new_str = new std::string("qwe");
	shared_ptr<std::string> _f_pt(new_str);
	shared_ptr<std::string> _f_pt2(_f_pt);
	
	REQUIRE(_f_pt->begin() == _f_pt2->begin());
	REQUIRE(_f_pt.unique() == false);
	REQUIRE(_f_pt.use_count() == 2);
	REQUIRE(_f_pt2.unique() == false);
	REQUIRE(_f_pt2.use_count() == 2);

	_f_pt2.reset();

	REQUIRE(_f_pt.unique());
	REQUIRE(_f_pt.use_count() == 1);

	_f_pt2.reset(a);
	//_f_pt2 = _f_pt;
	_f_pt.swap(_f_pt2);
	REQUIRE(_f_pt.unique());
	REQUIRE(_f_pt.use_count() == 1);
	REQUIRE(*_f_pt.get() == "asd");
}

#endif




#ifndef  TESTING


#include "shared.h"


int main()
{
	//std::string* str = new std::string("123");
	//std::shared_ptr<std::string> A(str);
	////std::shared_ptr<std::string> B(A);

	//A.reset();
	///*std::cout << *///A->~basic_string();
	//std::cout << *str;


	int mur = 8;
	int* murik = &mur;
	shared_ptr<int> murishe(murik);
	murishe.reset();




	//murishe.~shared_ptr();

	//shared_ptr<int> bbb(murishe);
	//std::cout << std::boolalpha << murishe.unique();






	////////////////////////
	//int* tmp = new int(5);
	//shared_ptr<int> aaa(tmp);
	//std::cout << *aaa;	
	//std::cout << *bbb;
	//bbb = aaa;

	//
	//



	//////////////////
	//std::cout << bbb.use_count() << std::endl;
	//std::cout << std::boolalpha<< bbb.unique() ;
	//
	////shared_ptr<int> asdf;
	//bbb.reset();
	//if (bbb) std::cout << "foo points to " << *bbb << '\n';
	//else  std::cout << "foo is null\n";
	//bbb.reset(new int);
	//*bbb = 10;
	//bbb = aaa;
	//aaa.reset(new int(11));
	//if (bbb) 
	//	std::cout << "foo points to " << *bbb << '\n';
	//bbb.swap(aaa);
	//std::cout << std::boolalpha << bbb.unique();

	//if (bbb)
	//	std::cout << "foo points to " << *bbb << '\n';

	//bbb.reset();
	//if (bbb)
	//	std::cout << "foo points to " << *bbb << '\n';
	//else  std::cout << "foo is null\n";

	/////*bbb = 10;

	return 0;
}




#endif // ! TESTING
