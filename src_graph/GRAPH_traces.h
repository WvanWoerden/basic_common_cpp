#ifndef INCLUDE_GRAPH_TRACES
#define INCLUDE_GRAPH_TRACES

#include "traces.h"
#include <vector>
#include <iostream>

template<typename Tgr>
std::vector<unsigned int> TRACES_GetCanonicalOrdering(Tgr const& eGR)
{
    DYNALLSTAT(int,lab1,lab1_sz);
    DYNALLSTAT(int,ptn,ptn_sz);
    DYNALLSTAT(int,orbits,orbits_sz);
    DYNALLSTAT(int,map,map_sz);
    static DEFAULTOPTIONS_TRACES(options);
    TracesStats stats;
    /* Declare and initialize sparse graph structures */
    SG_DECL(sg1);
    SG_DECL(cg1);

    int n = eGR.GetNbVert();

    /* Select option for canonical labelling */
    options.getcanon = TRUE;

    int m = SETWORDSNEEDED(n);
    nauty_check(WORDSIZE,m,n,NAUTYVERSIONID);

    DYNALLOC1(int,lab1,lab1_sz,n,"malloc");
    DYNALLOC1(int,ptn,ptn_sz,n,"malloc");
    DYNALLOC1(int,orbits,orbits_sz,n,"malloc");
    DYNALLOC1(int,map,map_sz,n,"malloc");

    /* Now make the first graph */
    int nbAdjacent = eGR.GetNbAdjacent();
    SG_ALLOC(sg1,n,nbAdjacent,"malloc");
    sg1.nv = n;              /* Number of vertices */
    sg1.nde = nbAdjacent;           /* Number of directed edges */
    for (int i=0; i<n; i++) {
      int eColor = 0;
      if (eGR.GetHasVertexColor())
        eColor = eGR.GetColor(i);
      ptn[i] = eColor;
    }
    int pos = 0;
    for (int i=0; i<n; i++) {
      std::vector<int> LAdj = eGR.Adjacency(i);
      int len = LAdj.size();
      sg1.d[i] = len;
      sg1.v[i] = pos;
      for (auto & eAdj : LAdj) {
        sg1.e[pos] = eAdj;
        pos++;
      }
    }

    Traces(&sg1,lab1,ptn,orbits,&options,&stats,&cg1);
    std::vector<unsigned int> V(n);
    for (int i=0; i<n; i++)
      V[lab1[i]] = i;

    DYNFREE(lab1,lab1_sz);
    DYNFREE(ptn,ptn_sz);
    DYNFREE(orbits,orbits_sz);
    DYNFREE(map,map_sz);
    SG_FREE(sg1);
    SG_FREE(cg1);
    return V;
}


template<typename Tgr>
std::vector<std::vector<unsigned int>> TRACES_GetListGenerators(Tgr const& eGR)
{
    DYNALLSTAT(int,lab1,lab1_sz);
    DYNALLSTAT(int,ptn,ptn_sz);
    DYNALLSTAT(int,orbits,orbits_sz);
    DYNALLSTAT(int,map,map_sz);
    static DEFAULTOPTIONS_TRACES(options);
    TracesStats stats;
    /* Declare the generator stuff */
    permnode *gens;
    options.generators = &gens;
    gens = NULL;
    freeschreier(NULL,&gens);
    options.getcanon = FALSE;

    /* Declare and initialize sparse graph structures */
    SG_DECL(sg1);
    int n = eGR.GetNbVert();
    int m = SETWORDSNEEDED(n);
    nauty_check(WORDSIZE,m,n,NAUTYVERSIONID);

    DYNALLOC1(int,lab1,lab1_sz,n,"malloc");
    DYNALLOC1(int,ptn,ptn_sz,n,"malloc");
    DYNALLOC1(int,orbits,orbits_sz,n,"malloc");
    DYNALLOC1(int,map,map_sz,n,"malloc");

    /* Now make the first graph */
    int nbAdjacent = eGR.GetNbAdjacent();
    SG_ALLOC(sg1,n,nbAdjacent,"malloc");
    sg1.nv = n;              /* Number of vertices */
    sg1.nde = nbAdjacent;           /* Number of directed edges */
    for (int i=0; i<n; i++) {
      int eColor = 0;
      if (eGR.GetHasVertexColor())
        eColor = eGR.GetColor(i);
      ptn[i] = eColor;
    }
    int pos = 0;
    for (int i=0; i<n; i++) {
      std::vector<int> LAdj = eGR.Adjacency(i);
      int len = LAdj.size();
      sg1.d[i] = len;
      sg1.v[i] = pos;
      for (auto & eAdj : LAdj) {
        sg1.e[pos] = eAdj;
        pos++;
      }
    }
    /* Calling Traces */
    std::cerr << "Before Traces\n";
    Traces(&sg1,lab1,ptn,orbits,&options,&stats,NULL);
    std::cerr << "After Traces\n";
    /* Extracting the list of generators */
    std::vector<std::vector<unsigned int>> ListGen;
    //
    permnode* pn = gens;
    do
      {
        std::cerr << "Inserting generator\n";
        std::vector<unsigned int> V(n);
        for (int i=0; i<n; i++)
          V[i] = pn->p[i];
        ListGen.push_back(V);
        //
        pn = pn->next;
      } while (pn != gens);

    DYNFREE(lab1,lab1_sz);
    DYNFREE(ptn,ptn_sz);
    DYNFREE(orbits,orbits_sz);
    DYNFREE(map,map_sz);
    SG_FREE(sg1);
    return ListGen;
}




#endif