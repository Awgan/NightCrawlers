#ifndef	READ_FILE_H_
#define READ_FILE_H_

#include <iostream>

#include <fstream>
#include <stdlib.h>
#include <string>

#include "graph_prop.h"
#include "position.h"
#include "property.h"
#include "terminal_info.h"


struct GPP {
	//structure for holding all properties
	struct in_GPP {
		Coordinate start_coord;
		Stru_property start_prop;
		Stru_graph_prop start_graph;
	};
	
	in_GPP * array;
	int numb;
	
	friend void fx( GPP & _gpp, const std::string _arr [][17] );
};

//TODO::change the '17' by const variable

void fx( GPP & _gpp, const std::string _arr [][17] ) {
	
	for ( int i = 0; i < _gpp.numb; ++i ) {
		
		_gpp.array[i].start_coord = { _arr[i][0], _arr[i][1], _arr[i][2] };
		
		/*for ( int j = 0; i < 17; ++i ) {
			
			if ( j >= 0 && j <= 4 ) {
				_gpp.array[j] = _arr[i][j];
			}
			else if ( j > 4 && j <= 8 ) {
				
			}
			else if ( j > 8 && j <= 17 ) {
				
			} 
			
		}*/
		
	}
	
}

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
				printf( "there was '#' character\n" );
			}
		}
		
		//get file size
		
		file_.clear(  );
		
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
			
			_gpp->array = new GPP::in_GPP [line_numb_];
			_gpp->numb = line_numb_;
			
				arr_pars_ = new std::string[line_numb_][17];
			
			
			file_.open( _fname );
			
			file_.read( tmp_file_, size );
			
			file_.close();
			
			//BEGIN : parsing data to structure
			std::string tmp_all_ = tmp_file_;
						
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
			
			//checking
			for ( int i = 0; i < line_numb_; ++i ) {
				for ( int j = 0; j < 17; ++j ) {
					std::cout << arr_pars_[i][j] << "";
				}
				std::cout << '\n';
			}
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
