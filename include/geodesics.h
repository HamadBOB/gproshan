#ifndef GEODESICS_H
#define GEODESICS_H

#include "include.h"
#include "che.h"

#include "include_arma.h"

/*!
	Compute the geodesics distances on a mesh from a source or multi-source. This class implements
	the Fast Marching algorithm without deal with obtuse triangles. Also, if the options PTP_CPU or
	PTP_GPU are enables, compute the geodesics distances executing the Parallel Toplesets Propagation
	algorithm.
*/
class geodesics
{
	public:
		enum option_t {	FM,				///< Execute Fast Marching algorithm
						PTP_CPU,		///< Execute Parallel Toplesets Propagation algorithm on CPU
						PTP_GPU,		///< Execute Parallel Toplesets Propagation algorithm on GPU
						HEAT_FLOW,		///< Execute Heat Flow - cholmod (CPU)
						HEAT_FLOW_GPU	///< Execute Heat Flow - cusparse (GPU)
						};

	public:
		index_t * clusters;			///< Clustering vertices to closest source.

	private:
		distance_t * distances;		///< Results of computation geodesic distances.
		index_t * sorted_index;		///< Sort vertices by topological level or geodesic distance.
		size_t n_vertices;			///< Number of vertices.
		size_t n_sorted;			///< Number of vertices sorted by their geodesics distances.

	public:
		geodesics(	che * mesh,							///< input mesh must be a triangular mesh.
					const vector<index_t> & sources,	///< source vertices.
					const option_t & opt = FM,			///< specific the algorithm to execute.
					const bool & cluster = 0,			///< if clustering vertices to closest source.
					const size_t & n_iter = 0, 			///< maximum number of iterations.
					const distance_t & radio = INFINITY	///< execute until the specific radio.
					);

		virtual ~geodesics();
		const distance_t & operator[](const index_t & i) const;
		const index_t & operator()(const index_t & i) const;
		const distance_t & radio() const;
		const index_t & farthest() const;
		const size_t & n_sorted_index() const;
		void copy_sorted_index(index_t * indexes, const size_t & n) const;
		void normalize();

	private:
		void execute(che * mesh, const vector<index_t> & sources, const size_t & n_iter, const distance_t & radio, const option_t & opt);
		void run_fastmarching(che * mesh, const vector<index_t> & sources, const size_t & n_iter, const distance_t & radio);
		void run_parallel_toplesets_propagation_cpu(che * mesh, const vector<index_t> & sources, const size_t & n_iter, const distance_t & radio);
		void run_parallel_toplesets_propagation_gpu(che * mesh, const vector<index_t> & sources, const size_t & n_iter, const distance_t & radio);
		void run_heat_flow(che * mesh, const vector<index_t> & sources);
		void run_heat_flow_gpu(che * mesh, const vector<index_t> & sources);

		distance_t update(index_t & d, che * mesh, const index_t & he, vertex & vx);
		distance_t planar_update(index_t & d, a_mat & X, index_t * x, vertex & vx);
};

#endif //GEODESICS_H

