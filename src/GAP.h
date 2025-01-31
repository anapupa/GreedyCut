#pragma once
#include "MeshCache.h"
#include "Auxiliary.h"
#include <Eigen/Core>
#include <Eigen/Geometry>

//#include "Eigen\src\Eigenvalues\EigenSolver.h"
#include <Eigen/Eigenvalues>
#include "Eigen/Dense"
#include "Eigen/Sparse"
#include "Eigen/SparseLU"
#include "Eigen/SVD"
#include "Solver/Solver.h"

class GAP
{
public:
	GAP(Mesh& mesh, MeshCache& MC, std::vector<std::pair<int, double>>& lmk);
	void Set(double InfluenceThreshold, double FilteringThreshold);
	void SetSolver(double convgence_con_rate, int MAX_ITER_NUM, double bound_distortion_K);
	void Run();
	~GAP();

	//BASIC
	void LandmarksClassification();
	std::vector<int> getResult() { return LmkResult; }

	//BPE
	void run_bpe();
	bool add1p(bool startfromtutte = false, int parr_count = 6);
	void init();
	void BPE();

	void init_src_matrix();
	void Pre_calculate();
	void TutteOp();
	void init_area();

	void Energysource();
	void Update_source_same_t();

	void SLIM();
	void max_step(const Eigen::VectorXd& xx, const Eigen::VectorXd& dd, double& step);
	double get_smallest_pos_quad_zero(double a, double b, double c);
	void backtracking_line_search(const Eigen::VectorXd& x, const Eigen::VectorXd& d, const Eigen::VectorXd& negetive_grad, double& alpha);
	void Energy(const Eigen::VectorXd& position, double& energyupdate);
	void local_coordinate_inverse(int i, double& p00, double& p01, double& p10, double& p11);
	double newton_equation(const double& a, const double& b, const double& K);

	void CM();
	void recover_to_src();

	//ADD1P
	void rePre_calculate(int i);
	void BPE(int i);
	void Energysource(int i);
	void Update_source_same_t(int N);
	void SLIM(int N);
	void max_step(const Eigen::VectorXd& xx, const Eigen::VectorXd& dd, double& step, int i);
	void backtracking_line_search(const Eigen::VectorXd& x, const Eigen::VectorXd& d, const Eigen::VectorXd& negetive_grad, double& alpha, int i);
	void Energy(const Eigen::VectorXd& position, double& energyupdate, int N);
	void CM(int i);
	void recover_to_src(int N);

private:
	//BASIC
	Mesh ClosedMesh, mEsh;
	MeshCache& MC;
	std::vector<std::pair<int, double>> landmark;

	std::vector<int> LmkFix, LmkCanditate, LmkResult;
	std::vector<int> v_seam, e_seam;
	std::vector<int> he2idx, idx2meshvid;
	double originmesh_area_sqrt;
	double time_consumption;

	int F_N, V_N;
	double g_norm;
	std::vector<double> area, area_uniform, area_src;
	std::vector<int> F0, F1, F2;
	std::vector<std::vector<int>> VV_ids;
	Eigen::VectorXd position_of_mesh;
	Eigen::VectorXd negative_grad_norm;
	Solver* solver;
	std::vector<int> solver_i, solver_ia, solver_ja;
	std::vector<double> solver_a, solver_b;

	double Intp_T_Min;
	double changetocm_flag;


	//PARAM
	double convgence_con_rate;
	int MAX_ITER_NUM;
	double bound_distortion_K;
	double InfluenceThreshold;
	double DistortionThreshold;

	//BPE
	double energy_prev_seam, energy_uniform, energy_area;
	std::vector<double> source_p00, source_p01, source_p10, source_p11;
	std::vector<double> update_p00, update_p01, update_p10, update_p11;

	std::vector<int> id_h00; std::vector<int> id_h01; std::vector<int> id_h02; std::vector<int> id_h03; std::vector<int> id_h04; std::vector<int> id_h05;
	std::vector<int> id_h11; std::vector<int> id_h12; std::vector<int> id_h13; std::vector<int> id_h14; std::vector<int> id_h15;
	std::vector<int> id_h22; std::vector<int> id_h23; std::vector<int> id_h24; std::vector<int> id_h25;
	std::vector<int> id_h33; std::vector<int> id_h34; std::vector<int> id_h35;
	std::vector<int> id_h44; std::vector<int> id_h45;
	std::vector<int> id_h55;

	//ADD1P
	std::vector<std::vector<int>> p_v_seam;
	std::vector<std::vector<int>> p_e_seam;
	std::vector<std::vector<int>> p_idx2meshvid;
	std::vector<std::vector<int>> p_he2idx;
	std::vector<std::vector<int>> p_F0;
	std::vector<std::vector<int>> p_F1;
	std::vector<std::vector<int>> p_F2;
	std::vector<std::vector<std::vector<int>>> p_VV_ids;
	std::vector<Eigen::VectorXd> p_position_of_mesh;
	std::vector<int> p_V_N;
	std::vector<int> p_F_N;
	std::vector<std::vector<int>> p_solver_i, p_solver_ia, p_solver_ja;
	std::vector<std::vector<double>> p_solver_a, p_solver_b;
	std::vector<std::vector<int>> p_id_h00;	std::vector<std::vector<int>> p_id_h01;	std::vector<std::vector<int>> p_id_h02;	std::vector<std::vector<int>> p_id_h03;	std::vector<std::vector<int>> p_id_h04;	std::vector<std::vector<int>> p_id_h05;
	std::vector<std::vector<int>> p_id_h11; std::vector<std::vector<int>> p_id_h12; std::vector<std::vector<int>> p_id_h13; std::vector<std::vector<int>> p_id_h14; std::vector<std::vector<int>> p_id_h15;
	std::vector<std::vector<int>> p_id_h22; std::vector<std::vector<int>> p_id_h23; std::vector<std::vector<int>> p_id_h24; std::vector<std::vector<int>> p_id_h25;
	std::vector<std::vector<int>> p_id_h33; std::vector<std::vector<int>> p_id_h34; std::vector<std::vector<int>> p_id_h35;
	std::vector<std::vector<int>> p_id_h44; std::vector<std::vector<int>> p_id_h45;
	std::vector<std::vector<int>> p_id_h55;

	std::vector<std::vector<double>> p_source_p00, p_source_p01, p_source_p10, p_source_p11;
	std::vector<std::vector<double>> p_update_p00, p_update_p01, p_update_p10, p_update_p11;
	std::vector<double> p_energy_uniform, p_energy_area, p_energy_prev_seam;
	std::vector<double> p_Intp_T_Min;
	std::vector<double> p_changetocm_flag;
	std::vector<double> p_g_norm;
	std::vector<Solver*> p_solver;
};