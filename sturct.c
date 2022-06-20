struct cvm_t_ {
    context_t *ctx; // working context
    mesh_t *skin;   // input skin mesh
    mesh_t *vol;    // output volume mesh
    INTEGER vol_dirty;

    tag_system_t
        *tag_system; /* FIXME : right now, the tag system is not propagated when
                        we have more that 1 parallel subdomain */

    cvm_state_t state;

    interrupt_callback_t interrupt_cb;
    void *interrupt_udata;
    message_callback_t message_cb;
    void *message_udata;
    int interrupt_now;

    char mbuff[TMMBUFF_LEN]; // temporary buffer for message passing

    /* parameters */
    integer abort_surface_insertion_on_intersection_detection;
    REAL anisotropic_ratio;
    INTEGER components_outermost_only;
    integer debug;
    element_generation_t element_generation;
    element_target_t element_target;
    REAL gradation;
    REAL gradation_log;
    gradation_mode_t gradation_mode;
    integer insert_surface;
    integer internal_points;
    cvm_internal_points_removal_effort_t internal_points_removal_effort;
    metric_intersection_t metric_intersection;
    metric_propagation_t metric_propagation;
    REAL metric_relative_thickness_on_surface;
    integer optimisation;
    integer optimisation_ignore_metric_for_element_shape;
    cvm_optimisation_level optim_level;
    integer remove_bounding_box;
    integer split_overconstrained_edges;
    integer split_overconstrained_tetrahedra;
    cvm_surface_insertion_effort_t surface_insertion_effort;
    REAL min_number_of_layers;
    integer surface_optimisation;
    real surface_optimisation_flat_angle;
    INTEGER_list_t *filter_components;
    integer remove_component_internal_surfaces;
    integer surface_optimisation_density;
    integer surface_optimisation_discard_metric;
    integer surface_optimisation_ignore_sharp_angles;
    integer surface_volume_optimisation;
    integer surface_insertion_recover_intersecting_entities;
    integer morph;
    REAL min_size;
    REAL max_size;
    size_mode_t size_mode;
    size_type_t size_type;
    meshgems_sizemap_iso_3d_t sizemap_iso;
    void *sizemap_iso_udata;
    meshgems_sizemap_aniso_3d_t sizemap_aniso;
    void *sizemap_aniso_udata;

    REAL worst_acceptable_quality;
    REAL worst_acceptable_user_quality;

    integer non_conformal_insertion;

    integer disable_surface_insertion;

    integer disable_boundary_layer_inserter;
    integer disable_hex_dominant_inserter;
    integer disable_cartesian_core_inserter;
    integer disable_regular_inserter;

    real boundary_layer_ridge_angle;
    integer boundary_layer_multinormal;
    integer boundary_layer_snapping;
    integer boundary_layer_imprinting;
    integer boundary_layer_cross_imprinting;
    integer boundary_layer_smoothing;

    REAL cfd_box;
    INTEGER cfd_box_tag;
    cvm_cfd_box_symmetry_t cfd_box_symmetry;
    INTEGER cfd_box_vertices[8];

    cvm_size_manager_t *size_manager;

    meshgems_sizemap_boundary_layer_around_mesh_face_t
        sizemap_boundary_layer_at_face;
    void *sizemap_boundary_layer_at_face_udata;

    meshgems_cvm_size_specification_t *size_specification;
    meshgems_cvm_morphing_specification_t *morphing_specification;

    integer complex_enforce_face_conformity;

    integer idealisation;
    integer idealisation_regularise_internal_surfaces;
    real idealisation_tolerance;
    integer resilient_insertion;
    integer resilient_insertion_allow_cracks;
    integer resilient_insertion_allow_partial_nru;
    integer resilient_insertion_intersect_surface_entities;
    integer resilient_insertion_move_surface_entities;
    integer resilient_insertion_refine_surface_entities;
    integer resilient_insertion_replace_surface_entities;

    integer resilient_propagate_tag_on_entity_collapse;
    integer verbose;
    cvm_volume_insertion_regularity_effort_t volume_insertion_regularity_effort;

    integer wrap_outside_component;
    real wrap_voxel_size;
    real wrap_hole_size;
    real wrap_penetration_depth;
    real wrap_minimum_penetration_depth;
    real wrap_gap_size;
    real wrap_avoid_external_surfaces_effort;
    real wrap_cost_factor_for_boundary_surface_face;
	integer wrap_smooth_surface;
	real wrap_smooth_surface_angle;
	real wrap_smooth_surface_effort;
    integer wrap_avoid_external_surfaces;
    integer wrap_enforce_gap_filling;
    integer wrap_gap_filling_tag;
    integer wrap_preserve_surface_genus;
    integer wrap_remove_internal_surface;
    real wrap_optimisation_effort;
    meshgems_mesh_t *input_wrapped_surface_mesh;

    meshgems_cvm_tetrahedron_quality_callback_t tetra_quality_cb;
    void *tetra_quality_udata;
    cvm_pyramid_quality_callback_t pyramid_quality_cb;
    void *pyramid_quality_udata;
    cvm_prism_quality_callback_t prism_quality_cb;
    void *prism_quality_udata;
    cvm_hexahedron_quality_callback_t hexahedron_quality_cb;
    void *hexahedron_quality_udata;

    /* callback for metric operations */
    cvm_internal_callback_propagate_metric_t internal_callback_propagate_metric;
    cvm_internal_callback_intersect_metric_t internal_callback_intersect_metric;
    /* callback for simplex volume and quality */
    cvm_internal_callback_tetrahedron_iar_6v_t
        internal_callback_tetrahedron_iar_6v;
    cvm_internal_callback_tetrahedron_6v_t internal_callback_tetrahedron_6v;
    /* callbacks for complex quality (volume cannot be properly defined
     * separately) */
    cvm_internal_callback_pyramid_iar_t internal_callback_pyramid_iar;
    cvm_internal_callback_prism_iar_t internal_callback_prism_iar;
    cvm_internal_callback_hexahedron_iar_t internal_callback_hexahedron_iar;

    // data for the tetra kernel

    /* Pseudo random number generator data */
    int rng;

    /* Vertex data */
    REAL *xyz;       // coordinates of vertices : 3*nv_max
    INTEGER voffset; // == 8 if bounding box is present in mesh
    INTEGER nv;      // number of vertices
    INTEGER nv_max;  // max number of vertices
    INTEGER nv_deleted;
    INTEGER nv_fix;      // FIXME : to be removed. useless
    INTEGER *vertex_tag; // size : n_vertex_tag
    INTEGER n_vertex_tag;
    REAL *size;
    REAL *w; // weight of vertices : nv_max
    INTEGER *vertex_boundary_layer_index;
    INTEGER *vertex_boundary_layer_origin_vertex;
    INTEGER *vertex_extra_tag;
    REAL *vertex_distance_to_original_surface;
    REAL *vertex_distance_to_original_surface_relative;
    cvm_vertex_properties_t *vertex_properties;
    cvm_vertex_extra_properties_t *vertex_extra_properties;
    cvm_metric_t *metric;

    /* Edge data */
    INTEGER *edges; // surface edges : 2*ne_max
    INTEGER *edge_non_conformity;
    cvm_edge_properties_t *edge_properties;
    INTEGER ne;     // number of edges
    INTEGER ne_max; // max number of edges
    INTEGER ne_deleted;
    INTEGER *edge_tag; // size : n_edge_tag
    INTEGER n_edge_tag;

    /* Triangle data */
    INTEGER *faces; // surface faces : 3*nf_max
    INTEGER *triangle_non_conformity;
    cvm_triangle_properties_t *triangle_properties;
    INTEGER *triangle_original_index;
    INTEGER nf;     // number of faces
    INTEGER nf_max; // max number of faces
    INTEGER nf_deleted;
    INTEGER *triangle_tag; // size : n_face_tag
    INTEGER n_triangle_tag;

    /* Surface grid data */
    struct s_rgrid3d_t_ *surface_grid;
    struct s_rgrid3d_box_iterator_t_ *surface_grid_it;

    /* Tetrahedron data */
    INTEGER *tetra;           // tetra vertices : 4*nt_max
    INTEGER *tetrahedron_tag; // tetra tag : nt_max
    INTEGER *neighbours;      // tetra neighbourhood data : 4*nt_max
    INTEGER *tetra_face_on_surface;
    INTEGER tetra_face_on_surface_is_valid;
    INTEGER *start; // vertices -> tetra  : nv_max
    INTEGER nt;     // number of tetra
    INTEGER nt_max; // max number of tetra
    INTEGER nt_deleted;
    cvm_tetrahedron_properties_t *tetrahedron_properties;
    REAL *center; // tetra center : 3*nt_max
    REAL *radius; // tetra radius: nt_max
    REAL *v6;
    REAL *iar;

    /* seed data (simplex) */
    INTEGER nseed;
    INTEGER nseed_max;
    cvm_seed_t *seed;
    oFI_map_t *vs_m;

    /* data for surface simplicial surface_complex. Note : a surface_complex can
       have internal vertices which belongs to to the triangle but do not belong
       to the element. Some surface_complex can also be un-inserted, in this
       case, complex_triangle_head[i] = 0 */

    /* surface complex id -> surface complex properties. size =
     * n_surface_complex_max */
    cvm_surface_complex_properties_t *surface_complex_properties;
    /* surface complex id -> surface complex priority. size =
     * n_surface_complex_max */
    INTEGER *surface_complex_priority;
    /* surface_complex id -> index in surface_complex_element_vertices for the
       head of vertex list making the corresponding element. size =
       n_surface_complex_max */
    INTEGER *surface_complex_element_vertices_head;
    /* array containing successive list of vertices for each surface_complex.
     * size = n_surface_complex_vertices_max*/
    INTEGER *surface_complex_element_vertices;
    /* surface_complex id -> index in surface_complex_triangle for the head of
      triangle list making the corresponding complex. size =
      n_complex_vertices_max */
    INTEGER *surface_complex_triangle_head;
    /* array containing successive list of triangle for each surface_complex.
     * size = n_surface_complex_vertices_max*/
    INTEGER *surface_complex_triangle;
    /* triangle simplex id -> surface_complex id. size = nf_max */
    INTEGER *triangle_surface_complex;

    INTEGER n_surface_complex;
    INTEGER n_surface_complex_max;
    INTEGER n_surface_complex_deleted;

    INTEGER n_surface_complex_element_vertices;
    INTEGER n_surface_complex_element_vertices_max;
    INTEGER n_surface_complex_element_vertices_deleted;

    INTEGER n_surface_complex_triangle;
    INTEGER n_surface_complex_triangle_max;
    INTEGER n_surface_complex_triangle_deleted;

    /* data for simplicial complex. Note : a complex can have internal vertices
       which belongs to to the tetra but do not belong to the element. Some
       complex can also be un-inserted, in this case, complex_tetra_head[i] = 0
     */

    /* complex id -> complex properties. size = n_complex_max */
    cvm_complex_properties_t *complex_properties;
    /* complex id -> complex priority. size = n_complex_max */
    INTEGER *complex_priority;
    /* complex id -> index in complex_element_vertices for the head of
       vertex list making the corresponding element. size = n_complex_max */
    INTEGER *complex_element_vertices_head;
    /* array containing successive list of vertice for each complex. size =
     * n_complex_vertices_max*/
    INTEGER *complex_element_vertices;
    /* complex id -> index in complex_tetra for the head of tetra list making
      the corresponding complex. size = n_complex_vertices_max */
    INTEGER *complex_tetra_head;
    /* array containing successive list of tetra for each complex. size =
     * n_complex_vertices_max*/
    INTEGER *complex_tetra;
    /* tetra simplex id -> complex id. size = nt_max */
    INTEGER *tetra_complex;

    INTEGER n_complex;
    INTEGER n_complex_max;
    INTEGER n_complex_deleted;

    INTEGER n_complex_element_vertices;
    INTEGER n_complex_element_vertices_max;
    INTEGER n_complex_element_vertices_deleted;

    INTEGER n_complex_tetra;
    INTEGER n_complex_tetra_max;
    INTEGER n_complex_tetra_deleted;

    /* global numbering data */
    INTEGER n_vertex_glo;
    INTEGER n_edge_glo;
    INTEGER n_triangle_glo;
    INTEGER n_tetrahedron_glo;
    INTEGER *
        vertex_glo; /**< global numbering for volume vertices (size :  nvglo) */
    INTEGER
    *edge_glo; /**< global numbering for volume vertices (size :  neglo) */
    INTEGER *triangle_glo;    /**< global numbering for volume vertices (size :
                                 nfglo) */
    INTEGER *tetrahedron_glo; /**< global numbering for volume tetrahedra (size
                                 : ntglo) */

    INTEGER entity_glo_input_range[cvm_entity_type_last + 1][2];
    INTEGER entity_glo_new_range[cvm_entity_type_last + 1][2];
    INTEGER seed_glo_input_range[2];
    INTEGER seed_glo_output_range[2];

    /* Edge hashing data */
    INTEGER eh_nh; /* size of the hash for edges */
    INTEGER *eh_h; /* size : neh*/
    INTEGER *eh_l; /* size : ne_max */

    /* Triangle hashing data */
    INTEGER fh_nh; /* size of the hash for triangles */
    INTEGER *fh_h; /* size : nfh*/
    INTEGER *fh_l; /* size : nf_max */

    /* Vertex -> Edge mapping data */
    INTEGER vem_n;
    INTEGER vem_nmax;
    INTEGER vem_gc_head;
    INTEGER *vem_head; /* size : nv */
    INTEGER *vem_data; /* size : vem_nmax */
    INTEGER *vem_link; /* size : vem_nmax */

    /* Edge -> Triangle mapping data */
    INTEGER efm_n;
    INTEGER efm_nmax;
    INTEGER efm_gc_head;
    INTEGER *efm_head; /* size : ne */
    INTEGER *efm_data; /* size : efm_nmax */
    INTEGER *efm_link; /* size : efm_nmax */

    /* Edge -> Tetra mapping data */
    INTEGER ecvm_n;
    INTEGER ecvm_nmax;
    INTEGER ecvm_gc_head;
    INTEGER *ecvm_head; /* size : ne */
    INTEGER *ecvm_data; /* size : ecvm_nmax */
    INTEGER *ecvm_link; /* size : ecvm_nmax */

    surface_entities_structure_t surface_entities_structure;

    INTEGER intersecting_edges;
    INTEGER intersecting_triangles;

    /* renormalisation applied to original coordinates : alpha+ beta * X */
    REAL alpha[3];
    REAL beta[3];
    REAL bbox_min[3];
    REAL bbox_max[3];
    REAL tight_bbox_min[3];
    REAL tight_bbox_max[3];
    REAL tight_cfd_object_min[3];
    REAL tight_cfd_object_max[3];

    struct i_rgrid3d_t_ *rgrid;
    struct i_rgrid3d_box_iterator_t_ *rgrid_it;
    struct i_rgrid3d_ellipse_iterator_t_ *rgrid_eit;

    F_hash_t *efh; /* hash of excluded faces */
    E_hash_t *eeh; /* hash of excluded edges */

    IE_hash_t
        *ir_veh; /* hash for unique reporting of vertex/edge intersections */
    IF_hash_t *
        ir_vfh; /* hash for unique reporting of vertex/triangle intersections */
    EE_hash_t
        *ir_eeh; /* hash for unique reporting of edge/edge intersections */
    EF_hash_t
        *ir_efh; /* hash for unique reporting of edge/triangle intersections */

    /* Marking data */
    int vbase;
    int *vmark;
    int ebase;
    int *edge_mark;
    int tbase;
    int *triangle_mark;
    int base;
    int *mark;

    unsigned char cbase;
    unsigned char *tetra_cmark;
    unsigned char obase;
    unsigned char *tetra_optimisation_mark;
    unsigned char fobase;
    unsigned char *triangle_optimisation_mark;
    unsigned char eobase;
    unsigned char *edge_optimisation_mark;

    INTEGER_list_t *tetra_mark_list; // the user of tetra_mark can also use this
                                     // list the way he sees fit

    INTEGER signal; // more optim needed before internal point insertion
    REAL aspect_ratio;

    REAL worst_iar;
    REAL worst_user_iar;

    INTEGER rvs;     // required vertices space (see
                     // cvm_prepare_required_entities_insertion)
    INTEGER res;     // required edges space (see
                     // cvm_prepare_required_entities_insertion)
    INTEGER rfs;     // required faces space (see
                     // cvm_prepare_required_entities_insertion)
    INTEGER rvstart; // required vertices insertion start index
    INTEGER fvtbi;   // first vertex to be inserted in the mesh
    INTEGER partial_insertion;

    INTEGER lirv; // last inserted required vertex

    int recursive_level;
    int deep_realloc;

    tetra_filter_function filter_fun;
    void *filter_data;

    REAL metric_ss_length;
    REAL metric_ss_length2;
    int metric_ss_level;

    REAL max_edge_length;
    REAL max_edge_length2;
    REAL min_edge_length;
    REAL min_edge_length2;

    REAL max_surface_edge_length;
    REAL max_surface_edge_length2;
    REAL min_surface_edge_length;
    REAL min_surface_edge_length2;

    /* Data for requested entities (on the fly entity insertion) */
    F_hash_t *rfh; /* hash of requested faces */
    E_hash_t *reh; /* hash of requested edges */
    I_hash_t *rvh; /* hash of requested vertices */

    /* Data for armor vertices grid */
    cvm_avg_t *avg;

    /* Data for the simplified geometry information */
    cvm_simplified_geometry_t *sg;

    /* The entities remaining to be inserted */

    /* seed data */
    INTEGER nrseed;
    INTEGER nrseed_max;
    cvm_seed_t *rseed;
    oFI_map_t *vrs_m;

    /* glo search data */
    II_map_t *gv_m;

    /* Parallel domain decomposition data */
    INTEGER index_first; /**< indice of this pdomain */
    INTEGER
    index_median; /**< indice of the median pdomain contained in this one */
    INTEGER
    index_last; /**< indice of the final pdomain contained in this one */
    INTEGER number_of_parallel_domains; /**< the total number of pdomains */

    REAL numerical_resolution;
    REAL numerical_resolution_scaled;
    INTEGER enforce_numerical_resolution;

    /* Statistics */
    INTEGER face_swap_try_count;
    INTEGER face_swap_count;
    INTEGER shell_build_try_count;
    INTEGER shell_build_count;
    INTEGER shell_swap_try_count;
    INTEGER shell_swap_count;
    INTEGER cavity_build_try_count;
    INTEGER cavity_build_count;
    INTEGER cavity_star_try_count;
    INTEGER cavity_star_count;
    INTEGER ball_build_count;
    INTEGER ball_build_try_count;
    INTEGER ball_move_try_count;
    INTEGER ball_move_count;
    INTEGER ball_optimize_try_count;
    INTEGER ball_optimize_count;
    INTEGER ball_collapse_try_count;
    INTEGER ball_collapse_count;

    real t0_cpu;
    real t0_real;
    real t1_cpu;
    real t1_real;
    real tlast_cpu;
    real tlast_real;
};

struct meshgems_cvm_session_t_ {
  context_t *ctx;
  interrupt_callback_t interrupt_cb;
  void *interrupt_udata;
  message_callback_t message_cb;
  void *message_udata;

  char *name;
  integer message_code;

  /* Input/output mesh data */
  mesh_t *input_mesh;
  mesh_t *output_mesh;
  mesh_t *output_surface_mesh;
  sizemap_t *output_sizemap;
  sizemap_t *output_distance_to_original_surface_sizemap;
  sizemap_t *output_distance_to_original_surface_sizemap_abs;
  int subdomain_meshes_count;
  int *subdomain_indices; /* size : n_subdomain_meshes */
  mesh_t **subdomain_meshes; /* size : subdomain_meshes_count */
  sizemap_t **subdomain_sizemaps; /* size : subdomain_meshes_count */
  ilist_t **subdomain_vertices_global_indices; /* size : subdomain_meshes_count */
  ilist_t **subdomain_edges_global_indices; /* size : subdomain_meshes_count */
  ilist_t **subdomain_triangles_global_indices; /* size : subdomain_meshes_count */
  ilist_t **subdomain_tetrahedra_global_indices; /* size : subdomain_meshes_count */
  integer vertex_global_count;
  integer edge_global_count;
  integer triangle_global_count;
  integer tetrahedron_global_count;
  integer high_element_order;

  /* Parameters */
  real anisotropic_ratio;
  integer components_outermost_only;
  ilist_t *filter_components;
  integer remove_component_internal_surfaces;
  integer discard_subdomains;
  meshgems_cvm_element_generation_t element_generation;
  meshgems_cvm_element_target_t element_target;
  real gradation;
  meshgems_cvm_gradation_mode_t gradation_mode;
  integer insert_surface;
  integer internal_points;
  meshgems_cvm_internal_points_removal_effort_t internal_points_removal_effort;
  real jacobian_threshold;
  real min_number_of_layers;
  real max_edge_length;
  real max_edge_length_r;
  real max_size;
  real max_size_r;
  real max_surface_edge_length;
  real max_surface_edge_length_r;
  integer merge_subdomains;
  real metric_ss_length;
  integer metric_ss_level;
  real min_edge_length;
  real min_edge_length_r;
  real min_size;
  real min_size_r;
  real min_surface_edge_length;
  real min_surface_edge_length_r;
  meshgems_cvm_metric_type_t metric_type;
  meshgems_cvm_metric_intersection_t metric_intersection;
  meshgems_cvm_metric_propagation_t metric_propagation;
  real metric_relative_thickness_on_surface;
  integer number_of_subdomains;
  integer number_of_threads;
  integer optimisation;
  integer optimisation_ignore_metric_for_element_shape;
  meshgems_cvm_optimisation_level_t optimisation_level;
  meshgems_cvm_parallel_strategy_t parallel_strategy;
  integer output_interfaces;
  integer remove_bounding_box;
  integer split_overconstrained_edges;
  integer split_overconstrained_tetrahedra;
  meshgems_cvm_surface_insertion_effort_t surface_insertion_effort;
  integer surface_optimisation;
  real surface_optimisation_flat_angle;
  integer surface_optimisation_density;
  integer surface_optimisation_discard_metric;
  integer surface_optimisation_ignore_sharp_angles;
  integer surface_volume_optimisation;
  integer surface_insertion_recover_intersecting_entities;
  integer non_conformal_insertion;
  integer morph;
  integer idealisation;
  integer idealisation_regularise_internal_surfaces;
  real idealisation_tolerance;
  integer resilient_insertion;
  integer resilient_insertion_allow_cracks;
  integer resilient_insertion_allow_partial_nru;
  integer resilient_insertion_intersect_surface_entities;
  integer resilient_insertion_move_surface_entities;
  integer resilient_insertion_refine_surface_entities;
  integer resilient_insertion_replace_surface_entities;
  integer resilient_propagate_tag_on_entity_collapse;
  
  integer use_c3d10m_jacobian;

  integer wrap_outside_component;
  real wrap_voxel_size;
  real wrap_hole_size;
  real wrap_penetration_depth;
  real wrap_minimum_penetration_depth;
  real wrap_gap_size;
  real wrap_avoid_external_surfaces_effort;
  real wrap_cost_factor_for_boundary_surface_face;
  integer wrap_smooth_surface;
  real wrap_smooth_surface_angle;
  real wrap_smooth_surface_effort;
  integer wrap_avoid_external_surfaces;
  integer wrap_enforce_gap_filling;
  integer wrap_gap_filling_tag;
  integer wrap_preserve_surface_genus;
  integer wrap_remove_internal_surface;
  real wrap_optimisation_effort;
  meshgems_mesh_t *input_wrapped_surface_mesh;

  meshgems_cvm_volume_insertion_regularity_effort_t volume_insertion_regularity_effort;

  integer disable_surface_insertion;

  integer disable_boundary_layer_inserter;
  integer disable_hex_dominant_inserter;
  integer disable_cartesian_core_inserter;
  integer disable_regular_inserter;

  real boundary_layer_ridge_angle;
  integer boundary_layer_multinormal;
  integer boundary_layer_snapping;
  integer boundary_layer_imprinting;
  integer boundary_layer_cross_imprinting;
  integer boundary_layer_smoothing;
  integer boundary_layer_auto_adaptation;

  real cfd_box;
  integer cfd_box_tag;
  meshgems_cvm_cfd_box_symmetry_t cfd_box_symmetry;

  integer complex_enforce_face_conformity;

  integer verbose;
  real worst_acceptable_quality;
  real worst_acceptable_user_quality;

  real numerical_resolution;
  integer enforce_numerical_resolution;
  
  meshgems_cvm_tetrahedron_quality_callback_t tetra_quality_cb;
  void *tetra_quality_udata;

  meshgems_sizemap_iso_mesh_vertex_t sizemap_iso_at_input_mesh_vertices;
  void *sizemap_iso_at_input_mesh_vertices_udata;
  meshgems_sizemap_aniso_mesh_vertex_t sizemap_aniso_at_input_mesh_vertices;
  void *sizemap_aniso_at_input_mesh_vertices_udata;

  meshgems_sizemap_iso_3d_t sizemap_iso;
  void *sizemap_iso_udata;
  meshgems_sizemap_aniso_3d_t sizemap_aniso;
  void *sizemap_aniso_udata;

  meshgems_sizemap_boundary_layer_around_mesh_face_t sizemap_boundary_layer_at_face;
  void *sizemap_boundary_layer_at_face_udata;

  meshgems_cvm_size_specification_t *size_specification;

  meshgems_cvm_morphing_specification_t *morphing_specification;

  FILE *debug_file;
  meshgems_license_t license;
  meshgems_license_t license_th1;
  meshgems_license_t license_th8;
  meshgems_license_t license_mesh_control;
  meshgems_license_t license_surface_optimisation;
  meshgems_license_t license_resilient;
  meshgems_license_t license_boundary_layer;
  integer banner_type;

  real last_progress;

  integer debug;
  integer valid;

  integer abort_surface_insertion_on_intersection_detection;

  integer error_count;
};
struct subdom_t_ {
    meshgems_cvm_session_t
        *cvms;  /**<  The tetra hpc session we belong to (pointed) */
    cvm_t *cvm; /**<  The tetra session we are working on (owned) */

    interrupt_callback_t interrupt_cb;
    void *interrupt_udata;

    mesh_t *msh; /**< output mesh */
    /* remaining entities */
    INTEGER nrv; /**< number of remaining vertices */
    INTEGER nre; /**< number of remaining edges */
    INTEGER nrf; /**< number of remaining faces */
    INTEGER nrq; /**< number of remaining quads */
    rv_size_type_t rv_size_type;

    rvertex_t *rv;  /**< remaining vertices (size = nrv) */
    REAL *rv_size; /**< size at remaining vertices (size = rv_size_type*nrv) */
    redge_t *re;    /**< remaining edges (size = nre) */
    rtriangle_t *rf; /**< remaining faces (size = nrf) */
    rquadrangle_t *rq; /**< remaining quads (size = nrq) */

    INTEGER niv; /**< index start for vertices in rv */
    INTEGER nie; /**< index start for vertices in rv */
    INTEGER nif; /**< index start for vertices in rv */

    INTEGER has_tetrahedron_tag;

    /* Data for building the outside */
    FI_map_t *fim;

    /* the special grid */
    sgrid_t *sgrid;
    REAL g;
    REAL lng;

    unsigned outside_initialized : 1;
};