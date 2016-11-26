//(c) 2016  white    "Source.cpp" as Sample source


#include <wlib_Json.hpp>
#include <string>
#include <fstream>

using namespace std;

void showError(const wlib::Json & json) {
	cout << "Is there any errors? : ";
	if (json.isError()) {
		cout << "unfortunately, yes." << endl;
		cout << "[ERROR MESSAGE : " << json.getError() << "]" << endl;
	}
	else cout << "no. Problem is nothing." << endl;
}

int main(void) {

	///////////////////////////
	// Prepare the json text.
	///////////////////////////

	//Read from test.json
	ifstream ifs("test.json");
	if (ifs.fail())
	{
		cerr << "Failed to open \"test.json\"." << endl;
		return -1;
	}

	istreambuf_iterator<char> it(ifs);
	istreambuf_iterator<char> last;
	string json_str(it, last);

	string error_string;

	//show the json_str.
	cout << "json_str:" << endl << json_str << endl << endl;

	
	//////////////////////////////////////
	// wlib::Json example body.
	//////////////////////////////////////

	//*** 1. parse and get.
	cout << "Parse..." << endl;
	wlib::Json test(json_str);
	//you can check the json is illegal or not by test.isError() or test.getError().
	showError(test);
	cout << endl << endl;


	if (!test.isError()) {
		//parse successfully.

		//*** 2. right accesses.
		cout << endl << "======== RIGHT ACCESSES =========" << endl;
		cout << "year           => " << test["year"].num() << endl;		//year data is number
		cout << "title          => " << test["title"].str() << endl;		//title data is string
		cout << "info.rating    => " << test["info"]["rating"].num() << endl;
		cout << "info.actors[0] => " << test["info"]["actors"][0].str() << endl;

		showError(test);
		cout << endl << endl;




		//*** 3. wrong.

		//** 3.1 there is no such key.
		cout << endl << "======== NO KEY =========" << endl;
		cout << "hogehoge => " << test["hogehoge"].str() << endl;
		showError(test);
		cout << endl << endl;


		//** 3.2 mismatched type
		//[NOTICE] mismatched type error is not able to catch by test.isError() or test.getError().
		//report the error to error_str only.
		cout << endl << "======== MISMATCHED TYPE =========" << endl;
		cout << "info.rank as string => " << test["info"]["rank"].str() << endl;
		showError(test);
		cout << endl << endl;


		//** 3.3 index out of bounds
		cout << endl << "======== INDEX OUT OF BOUNDS =========" << endl;
		cout << "info.genres[3] => " << test["info"]["genres"][3].str() << endl;
		showError(test);
		cout << endl << endl;


		//** 3.4 not object
		cout << endl << "======== NOT OBJECT =========" << endl;
		cout << "info.plot.text => " << test["info"]["plot"]["text"].str() << endl;
		showError(test);
		cout << endl << endl;


		//** 3.5 not array
		cout << endl << "======== NOT ARRAY =========" << endl;
		cout << "info[2] => " << test["info"][2].str() << endl;
		showError(test);
		cout << endl << endl;


		//** 3.6 not value
		cout << endl << "======== NOT VALUE =========" << endl;
		//This reports as "Mismatched Type".
		cout << "info => " << test["info"].str() << endl;
		showError(test);
		cout << endl << endl;

	}

}