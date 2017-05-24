/*******************************************************
 * MC658 - Projeto e Analise de Algoritmo III - 1s2017
 * Prof: Flavio Keidi Miyazawa
 * PED: Edson Ticona Zegarra
 ******************************************************/
#include "transportation.h"

///Preencher aqui para facilitar a correcao. 
// Nome1: Matheus Ferreira Tavares Boy
// RA1: 103501
// Nome2: Andre Nogueira Brandao
// RA2: 116130

// Gurobi Optimizer version 6.0.2 build v6.0.2rc0 (linux64)


///
// PL function
///
bool pl(ListBpGraph& g, ListBpGraph::EdgeMap<int> &c, ListBpGraph::NodeMap<int> &v, ListBpGraph::EdgeMap<int> &sol, int tMax){
	GRBEnv env = GRBEnv();
	GRBModel model = GRBModel(env);
	GRBLinExpr expr;
	model.set(GRB_IntAttr_ModelSense, GRB_MINIMIZE);
	env.set(GRB_DoubleParam_TimeLimit, tMax);

	// funcao objetivo
	// min SUM(SUM(vij * xij)
	ListBpGraph::EdgeMap<GRBVar> x(g);
    for ( ListBpGraph::EdgeIt e(g); e!=INVALID; ++e ){
        // xij >= 0
        x[e]=model.addVar(0.0,GRB_INFINITY,c[e],GRB_CONTINUOUS,"");
	}
    model.update();

    // RedNode == terminal
    // para cada i faca SUM(xij) = ti
    for ( ListBpGraph::RedNodeIt rn(g); rn!=INVALID; ++rn ) {
        GRBLinExpr expr;
        for ( ListBpGraph::IncEdgeIt e(g,rn); e!=INVALID; ++e ){
            expr += x[e];
        }
        model.addConstr(expr == v[rn]);
    }

    // BlueNode == roteador
    // para cada j faca SUM(xij) <= cj
    for ( ListBpGraph::BlueNodeIt bn(g); bn!=INVALID; ++bn ) {
        GRBLinExpr expr;
        for ( ListBpGraph::IncEdgeIt e(g,bn); e!=INVALID; ++e ){
            expr += x[e];
        }
        model.addConstr(expr <= v[bn]);
    }
    
    model.update();
    
    try {
        model.optimize();
        for ( ListBpGraph::EdgeIt e(g); e!=INVALID; ++e ){
            sol[e]=x[e].get(GRB_DoubleAttr_X);
	    }
    }
    catch(GRBException e) {
        for ( ListBpGraph::EdgeIt e(g); e!=INVALID; ++e ){
            sol[e]=x[e].get(GRB_DoubleAttr_X);
	    }
        std::cerr << "Codigo de erro = " << e.getErrorCode() << std::endl;
        std::cerr << e.getMessage();
	    return false;
    }
	return true;
}
