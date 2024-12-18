#include "test.hpp"

#include <unordered_array.hpp>
#include <strong_type.hpp>
#include <reflected_function.hpp>

#include <stdio.h>

struct abstract_car
{
	const char* strName;
	int numWheels;
	float weightInKg;
};

void test::test_unordered_array()
{
	printf( " ---- unordered_array test ----\n" );
	
	{
		arg::unordered_array<uint16_t, const char*> names;

		printf( "size:   %zu\ncount:  %zu\n\n", names.size(), names.count() );

		uint16_t name1 = names.emplace( "car" );         // 1
		uint16_t name2 = names.emplace( "sail" "boat" ); // 2
		uint16_t name3 = names.emplace( "plane" );       // 3

		printf( "size:   %zu\ncount:  %zu\n\n", names.size(), names.count() );

		const char* name1str = names.at( name1 );      // "car"
		const char* name2str = names.at( name2 );      // "sailboat"
		const char* name3str = names.at( name3 );      // "plane"

		names.erase( name1 );                          // erase "car"
		name1 = 0;                                     // make sure to invalidate

		printf( "size:   %zu\ncount:  %zu\n\n", names.size(), names.count() );

		uint16_t name5 = names.emplace( "bicycle" );     // 1
		const char* name5str = names.at( name5 );     // "bicycle"

		printf( "size:   %zu\ncount:  %zu\n\n", names.size(), names.count() );

		names.clear();

		printf( "size:   %zu\ncount:  %zu\n\n", names.size(), names.count() );
	}

	arg::unordered_array<uint16_t, abstract_car> cars;
	uint16_t saabID  = cars.emplace( "Saab 95 v4", 4, 946.0f );
	uint16_t robinID = cars.emplace( "Reliant Robin", 3, 436.0f );

	printf( "%s weighs %fkg\n", cars.at( saabID ).strName, cars.at( saabID ).weightInKg );
	printf( "%s weighs %fkg\n", cars[ robinID ].strName, cars[ robinID ].weightInKg );

	printf( " ------------------------------\n" );
}

void test::test_array_view()
{

}

typedef arg::strong_type<uint16_t, struct handle1_kt> handle1_t;
typedef arg::strong_type<uint16_t, struct handle2_kt> handle2_t;

static uint16_t get_strong_value( handle1_t _t ) { 
	return _t.value; 
}

void test::test_strong_type()
{
	printf( " ------ strong_type test ------\n" );
	
	handle1_t someHandle1{ 1 };
	handle2_t someHandle2{ 2 };
	
	printf( "handle1_t: %i\n", get_strong_value( someHandle1 ) );
	// printf( "%i", get_strong_value( someHandle2 ) ); // strong type mismatch, compiler error
	// uint16_t u16 = someHandle1; // compiler error

	printf( " ------------------------------\n" );
}

struct testThing
{
	float f;
	int a;
};

float example( int32_t _i, float _f, testThing _ptr )
{
	return static_cast<float>( _i ) + _f;
}

void test::test_reflected_function()
{
	printf( " --- reflected_function test --\n" );

	arg::reflected_function<example> efunc( "example" );
	printf( "symbol: %s\n", efunc.symbol() );
	printf( "%zu parameters\n", efunc.arg_count() );
	printf( "name:  %s %s(", efunc.ret_name(), efunc.name() );

	auto names = efunc.arg_names();
	for( size_t i = 0; i < names.size(); i++ )
	{
		if( i != 0 )
			printf( ", " );
		printf( "%s", names[ i ] );
	}
	printf( ")\n" );

	printf( "%f\n", efunc( 3, 0.141592, testThing{} ) );

	printf( " ------------------------------\n" );
}
