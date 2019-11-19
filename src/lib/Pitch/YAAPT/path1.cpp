//
// Created by rika on 10/11/2019.
//

#include <iostream>
#include "YAAPT.h"

using namespace Eigen;

void YAAPT::path1(ConstRefXXd local, ConstRefXXXd trans, RefXi path)
{
    const int M = local.rows();
    const int N = local.cols();

    // Initializing several desired matrix.
    ArrayXXi PRED;
    ArrayXi p;
    ArrayXd PCOST;
    ArrayXd CCOST;

    PRED.setZero(M, N);
    path.setZero();
    p.setZero(N);
    PCOST.setZero(M);
    CCOST.setZero(M);

    // Initializing the previous costs.
    for (int j = 0; j < M; ++j) {
        PCOST(j) = local(j, 0);
    }

    // This loop is the main loop.
    for (int i = 1; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            // Get the lowest cost.
            CCOST(j) = 1e+30;

            for (int k = 0; k < M; ++k) {
                // Deciding the optimal path between two points in two consecutive columns.
                if (PCOST(k) + trans(k, j, i) <= CCOST(j)) {
                    CCOST(j) = PCOST(k) + trans(k, j, i);
                    PRED(j, i) = k;
                }
            }

            if (CCOST(j) >= 1e+30) {
                std::cerr << "path1: CCOST > 1.0e+30, stop." << std::endl;
                return;
            }

            // New cost is calculated with the sum.
            CCOST(j) += local(j, i);
        }

        // Using new costs to update previous costs.
        PCOST = CCOST;

        // Obtaining the points with lowest cost in every column.
        CCOST.minCoeff(&p(i));
    }

    // Backtracking.
    path(N - 1) = p(N - 1);
    for (int i = N - 2; i >= 0; --i) {
        path(i) = PRED(p(i + 1), i + 1);
    }
}