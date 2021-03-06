#pragma once
#include <mathsat.h>
#include <vector>
#include <string>
#include <map>

class IMathSAT {
  msat_config cfg;
  msat_env env;
public:
  typedef msat_term term;
  typedef msat_type type;
  typedef msat_decl decl;
  typedef int interp_group;
  class model_iterator;
  IMathSAT(const char* logic, bool interpolation=true);
  ~IMathSAT();
  type bool_type();
  type int_type();
  term error_term();
  bool is_error_term(term t);
  decl make_decl(const std::string& name,type tp);
  term make_var(decl d);
  term make_eq(const std::vector<term>& args);
  term make_true();
  term make_false();
  term make_and(const std::vector<term>& args);
  term make_or(const std::vector<term>& args);
  term make_implication(const std::vector<term>& args);
  term make_not(term t);
  term make_ite(term c,term t,term f);
  term make_number(std::string& str);
  term make_lt(term t1,term t2);
  term make_leq(term t1,term t2);
  term make_gt(term t1,term t2);
  term make_geq(term t1,term t2);
  term make_plus(const std::vector<term>& args);
  term make_times(term t1,term t2);
  term make_minus(term t1,term t2);
  std::string term_to_string(term t);
  void assert(term t);
  void push();
  void pop();
  bool check_sat();
  interp_group create_interp_group();
  void set_interp_group(interp_group grp);
  term interpolate(const std::vector<interp_group>& grps);
  term translate_term(term t,std::map<decl,decl>& translation);
  model_iterator create_model_iterator();

  class model_iterator {
    msat_model_iterator it_;
  public:
    model_iterator(msat_model_iterator it);
    ~model_iterator();
    bool has_next();
    void next(term*t,term*v);
  };
};

bool operator<(const IMathSAT::decl,const IMathSAT::decl);
