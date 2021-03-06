/*    Copyright (C) 2013  kklloh

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#ifndef SOR_SOLVER_HH
#define SOR_SOLVER_HH

#include "StaggeredGrid.hh"
#include "Geometry2D.hh"
#include <omp.h>


class SORSolver
{
public:
   // Constructor to manually create SORSolver
   SORSolver();
   SORSolver ( int iterMax, real TOL, real W, std::string nrmtype );

   // Constructor to create a SORSolver from a parsed configuration file
   SORSolver ( const FileReader & configuration );
   // solve the pressure equation on the staggered grid
   bool solve( StaggeredGrid & grid );
   // solve the pressure equation on the staggered grid with obstacles
   bool solve_CG( StaggeredGrid & grid, Geometry2D& mesh);
   bool solve_PCG( StaggeredGrid & grid, Geometry2D& mesh);
   bool solve_SORRB( StaggeredGrid & grid, Geometry2D& mesh);
   int iterations();
   real residualnorm();
   inline int eps_E(int i, int j, Geometry2D&mesh);
   inline int eps_N(int i, int j, Geometry2D&mesh);
   inline int eps_W(int i, int j, Geometry2D&mesh);
   inline int eps_S(int i, int j, Geometry2D&mesh);

private:
   int iterMax_,Hbctype_,Vbctype_;
   int iter_, rescheckfreq_;
   real W_;
   real TOL_;
   real residual;
   Array sol_;
   std::string nrmtype_;
	 void setBC(Array &Q,const int & nGhost);
	 void setBC(Array &Q,Geometry2D &mesh,const int & nGhost);
};


inline int SORSolver::eps_E(int i, int j, Geometry2D&mesh){
	int epsE = (mesh.geom_isFluid(i+1,j))? 1 : 0;
	return epsE;
}
inline int SORSolver::eps_S(int i, int j, Geometry2D&mesh){
	int epsS = (mesh.geom_isFluid(i,j-1))? 1 : 0;
	return epsS;
}
inline int SORSolver::eps_W(int i, int j, Geometry2D&mesh){
	int epsW = (mesh.geom_isFluid(i-1,j))? 1 : 0;
	return epsW;
}
inline int SORSolver::eps_N(int i, int j, Geometry2D&mesh){
	int epsN = (mesh.geom_isFluid(i,j+1))? 1 : 0;
	return epsN;
}


#endif //SOR_SOLVER_HH




