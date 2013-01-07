#pragma once

#include "CAdata.h"


class CA1d : public CAdata {
public:
	
	void setup(int rx) {
		dim.x = rx;
		
		numcells = dim.x;
		currentGrid.assign( numcells, 0 );
		nextGrid.assign( numcells, 0 );

		setNumBits(8);
		setCenter1();
		
		cout << this << " CA1d init: " + ofToString(dim.x) + " " + ofToString(numcells) + "\n";
	}
	
	void set(int locx, int val) {

		currentGrid[locx] = val;
	}
	
	vector<int>* get() {
		return &currentGrid;
	}
	
	void setCenter1() {
		currentGrid[(int) (dim.x * 0.5)] = 1;
	}
	
	void update() {
		
		for (int x = 1; x < dim.x - 1; x++) {
			int count = countCells(x);
			setNextGrid(x, rules[count]);		
		}
		
		//swap grids 2do
		int temp;
		for(int i=0; i<dim.x; i++){
			temp =  currentGrid[i] ;
			currentGrid[i] = nextGrid[i];
			nextGrid[i] = temp;
		}

		
	}
	
	void setNextGrid(int x, float val) {
			nextGrid[x] = val;
	}
	
	int countCells(int x) {	
		//current pattern	111	110	101	100	011	010	001	000
		int num = 0;
		for (int i = 0; i < 3; i++) {
			if (currentGrid[x-1+i] == 1)
				num |= (1 << i);
		}		
		return num;
	}
	

};