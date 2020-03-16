/*
 * NearestPoints.cpp
 */

#include <limits>
#include <thread>
#include <algorithm>
#include <cmath>
#include "NearestPoints.h"
#include "Point.h"

const double MAX_DOUBLE = std::numeric_limits<double>::max();

Result::Result(double dmin, Point p1, Point p2) {
	this->dmin = dmin;
	this->p1 = p1;
	this->p2 = p2;
}

Result::Result() {
	this->dmin = MAX_DOUBLE;
	this->p1 = Point(0,0);
	this->p2 = Point(0,0);
}

/**
 * Auxiliary functions to sort vector of points by X or Y axis.
 */
static void sortByX(vector<Point> &v, int left, int right)
{
	std::sort(v.begin( ) + left, v.begin() + right + 1,
		[](Point p, Point q){ return p.x < q.x || (p.x == q.x && p.y < q.y); });
}

static void sortByY(vector<Point> &v, int left, int right)
{
	std::sort(v.begin( ) + left, v.begin() + right + 1,
		[](Point p, Point q){ return p.y < q.y || (p.y == q.y && p.x < q.x); });
}

/**
 * Brute force algorithm O(N^2).
 */
Result nearestPoints_BF(vector<Point> &vp) {
	Result res;
	res.dmin = MAX_DOUBLE;

    for (auto &p1 : vp) {
        for (auto &p2 : vp) {
            if (!(p1 == p2)) {
                double dist = p1.distance(p2);
                if (res.dmin > dist) {
                    res.p1 = p1;
                    res.p2 = p2;
                    res.dmin = dist;
                }
            }
        }
    }

	return res;
}

/**
 * Improved brute force algorithm, that first sorts points by X axis.
 */
Result nearestPoints_BF_SortByX(vector<Point> &vp) {
	sortByX(vp, 0, vp.size()-1);
	return nearestPoints_BF(vp);
}


/**
 * Auxiliary function to find nearest points in strip, as indicated
 * in the assignment, with points sorted by Y coordinate.
 * The strip is the part of vp between indices left and right (inclusive).
 * "res" contains initially the best solution found so far.
 */
static void npByY(vector<Point> &vp, int left, int right, Result &res) {
    for (int i = left; vp[i].x <= right; i++) {
        for (int j = i + 1; vp[j].x <= right; j++) {
            double distance = vp[i].distance(vp[j]);
            if (distance < res.dmin) {
                res.dmin = distance;
                res.p1 = vp[i];
                res.p2 = vp[j];
            }
        }
    }
}

Result min(Result& A, Result& B) {
    return (A.dmin < B.dmin) ? A : B;
}

/**
 * Recursive divide and conquer algorithm.
 * Finds the nearest points in "vp" between indices left and right (inclusive),
 * using at most numThreads.
 */
static Result np_DC(vector<Point> &vp, int left, int right, int numThreads) {

    if (vector<Point>(vp.begin() + left, vp.begin() + right + 1).size() <= 3) {
        return nearestPoints_BF(vp);
    }

	// Divide in halves (left and right) and solve them recursively,
	// possibly in parallel (in case numThreads > 1)
    int middle = (left + right) / 2;
    Result leftBest, rightBest;
	if (numThreads > 1) {
	    thread t1([&] () { leftBest = np_DC(vp, left, middle, numThreads / 2); });
	    rightBest = np_DC(vp, middle + 1, right, numThreads / 2);
	    t1.join();
	}
	else {
        leftBest = np_DC(vp, left, middle, 1);
        rightBest = np_DC(vp, middle + 1, right, 1);
	}

	// Select the best solution from left and right
	Result best = min(leftBest, rightBest);

	// Determine the strip area around middle point
	double stripMiddle = (vp[middle].x + vp[middle + 1].x) / 2.0;
	int i;
	for (i = 0; i < vp.size(); i++) {
	    if ((stripMiddle - vp[i].x) <= best.dmin) {
            break;
	    }
	}
	int j;
	for (j = vp.size() - 1; j > 0; j--) {
	    if ((vp[j].x - stripMiddle) <= best.dmin) {
            break;
	    }
	}

    // Order points in strip area by Y coordinate
    sortByY(vp, i, j);

	// Calculate nearest points in strip area (using npByY function)
	npByY(vp, i, j, best);

	// Reorder points in strip area back by X coordinate
	sortByX(vp,left,right);

	return best;
}


/**
 * Defines the number of threads to be used.
 */
static int numThreads = 1;
void setNumThreads(int num)
{
	numThreads = num;
}

/*
 * Divide and conquer approach, single-threaded version.
 */
Result nearestPoints_DC(vector<Point> &vp) {
	sortByX(vp, 0, vp.size() -1);
	return np_DC(vp, 0, vp.size() - 1, 1);
}


/*
 * Multi-threaded version, using the number of threads specified
 * by setNumThreads().
 */
Result nearestPoints_DC_MT(vector<Point> &vp) {
	sortByX(vp, 0, vp.size() -1);
	return np_DC(vp, 0, vp.size() - 1, numThreads);
}
