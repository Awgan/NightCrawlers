#ifndef	READ_FILE_H_
#define READ_FILE_H_

#include <iostream>

#include <fstream>
#include <stdlib.h>
#include <string>

#include "comm_const.h"
#include "graph_prop.h"
#include "position.h"
#include "property.h"


struct GPP {
	//structure for holding all properties
	struct in_GPP {
		Coordinate start_coord;
		Stru_property start_prop;
		Stru_graph_prop start_graph;
	};
	
	in_GPP * array;
	int numb;
	
	friend void gpp_transfer( GPP & _gpp, const std::string _arr [][17] );
};

Point_type p_type_conv( const std::string & _str ) {
	
	//Point_type --> { neutral = 0, hero = 1, bullet = 2, obstacle = 3 };
	
	if ( _str == "neutral" ) {
		return Point_type::neutral;
	}
	else if ( _str == "hero" ) {
		return Point_type::hero;
	}
	else if ( _str == "bullet" ) {
		return Point_type::bullet;
	}
	else if ( _str == "obstacle" ) {
		return Point_type::obstacle;
	}
		
	return Point_type::neutral;
}

//TODO::change the '17' by const variable

void gpp_transfer( GPP & _gpp, const std::string _arr [][17] ) {
		
	for ( int i = 0; i < _gpp.numb; ++i ) {
									//		x						y						z					direction
		_gpp.array[i].start_coord = { std::stoi(_arr[i][0]), std::stoi(_arr[i][1]), std::stoi(_arr[i][2]), dir_conv( _arr[i][3] ) };
		
		_gpp.array[i].start_prop = { p_type_conv( _arr[i][4] ), std::stoi(_arr[i][5]), std::stoi(_arr[i][6]), std::stoi(_arr[i][7]), std::stoi(_arr[i][8]), std::stoi(_arr[i][9]), std::stoi(_arr[i][10]), std::stoi(_arr[i][11]) };
		
		_gpp.array[i].start_graph.init_arr(p_type_conv( _arr[i][4] ));
		_gpp.array[i].start_graph = { _arr[i][12], std::stoi(_arr[i][13]), NULL, 0, std::stoi(_arr[i][15]), std::stoi(_arr[i][16]) };
		
	}
	
}

/******************************************************************/

void read_conf_file ( const char * _fname, GPP * _gpp ) {
	// _fname 		=> file name of object properties
	// _aar_gpp 	=> poiter to array of GPP structures
	
	
	std::ifstream file_;
	file_.open( _fname, std::ifstream::binary );
	
	std::string line_;
	char * tmp_file_;
	int line_numb_ = 0;
	std::string (* arr_pars_) [17];
		
	if ( file_.is_open() ) {
		
		while ( std::getline ( file_, line_ ) ) {
			
			if ( line_[0] != '#' ) {
				line_numb_++;
			}
			else {
				
			}
		}
		
		//get file size
		
		file_.clear( );
		
		file_.seekg( 0, file_.end );
		int size = file_.tellg();
		
		if ( size > 0 ) {
			
			tmp_file_ = new char [ size ];
			
		}
		else {
			std::cout << "Error of getting file size; function tellg()\n";
		}
		//END
		
		file_.close();
		
		//
		if ( line_numb_ > 0 ) {
			
			_gpp->numb = line_numb_;
			_gpp->array = new GPP::in_GPP [line_numb_];
			
			
				arr_pars_ = new std::string[line_numb_][17];
			
			
			file_.open( _fname );
			
			file_.read( tmp_file_, size );
			
			file_.close();
			
			//BEGIN : parsing data to structure
			std::string tmp_all_ = tmp_file_; //changing c-string to string
			
			int start_of_read_ = tmp_all_.find_last_of( '\n', tmp_all_.find(',') ) + 1;
			int end_of_read_ = 0;
			std::string pos_1_;
			
			for ( int i = 0; i < line_numb_; ++i ) {
				int y;
				y = 0;
				end_of_read_ = 0;
				while( tmp_all_[end_of_read_+1] != '\n' ) {
				
					end_of_read_ = tmp_all_.find_first_of( ",;", start_of_read_ );
						
					pos_1_ = tmp_all_.substr( start_of_read_, end_of_read_ - start_of_read_ );
					
					arr_pars_[i][y] = pos_1_;
					
					start_of_read_ = end_of_read_ + 1;
					++y;				
				}				
			}
			//END : parsing data to structure
			
			gpp_transfer( *_gpp, arr_pars_ );
						
			//
			
		}
		else {
			std::cout << "there are not lines with data; _line_numb_ = " << line_numb_ << std::endl;
			delete [] tmp_file_;
			file_.close();
			return;
		}
	
	}
	
	else {
		std::cout << "read_conf_file() :: file is not open\n"; 
		return;
	}
	
delete [] tmp_file_;	
	
}

#endif
