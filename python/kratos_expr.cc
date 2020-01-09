#include "kratos_expr.hh"

#include <pybind11/cast.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

#include "kratos_debug.hh"

namespace py = pybind11;
using std::shared_ptr;

std::optional<std::pair<std::string, uint32_t>> get_fn_ln(uint32_t num_frame_back);

void init_common_expr(py::class_<kratos::Var, ::shared_ptr<kratos::Var>> &class_) {
    namespace py = pybind11;
    using std::shared_ptr;
    using namespace kratos;
    // see how available object overloads here: https://docs.python.org/3/reference/datamodel.html
    class_.def("__repr__", &Var::to_string)
        .def(
            "__invert__", [](const Var &var) -> Expr & { return ~var; },
            py::return_value_policy::reference)
        .def(
            "__neg__", [](const Var &var) -> Expr & { return -var; },
            py::return_value_policy::reference)
        .def(
            "__pos__", [](const Var &var) -> Expr & { return +var; },
            py::return_value_policy::reference)
        .def(
            "__add__", [](const Var &left, const Var &right) -> Expr & { return left + right; },
            py::return_value_policy::reference)  // NOLINT
        .def(
            "__add__",
            [](const Var &left, const int64_t &right) -> Expr & {
                return left + convert_int_to_const(left, right);
            },
            py::return_value_policy::reference)  // NOLINT
        .def(
            "__add__",
            [](const int64_t &left, Var &right) -> Expr & {
                return convert_int_to_const(left, right) + right;
            },
            py::return_value_policy::reference)  // NOLINT
        .def(
            "__sub__", [](const Var &left, const Var &right) -> Expr & { return left - right; },
            py::return_value_policy::reference)  // NOLINT
        .def(
            "__sub__",
            [](const Var &left, const int64_t &right) -> Expr & {
                return left - convert_int_to_const(left, right);
            },
            py::return_value_policy::reference)  // NOLINT
        .def(
            "__sub__",
            [](const int64_t &left, Var &right) -> Expr & {
                return convert_int_to_const(left, right) - right;
            },
            py::return_value_policy::reference)  // NOLINT
        .def(
            "__mul__", [](const Var &left, const Var &right) -> Expr & { return left * right; },
            py::return_value_policy::reference)  // NOLINT
        .def(
            "__mul__",
            [](const Var &left, const int64_t &right) -> Expr & {
                return left * convert_int_to_const(left, right);
            },
            py::return_value_policy::reference)  // NOLINT
        .def(
            "__truediv__",
            [](const int64_t &left, Var &right) -> Expr & {
                return convert_int_to_const(left, right) / right;
            },
            py::return_value_policy::reference)  // NOLINT
        .def(
            "__truediv__", [](const Var &left, const Var &right) -> Expr & { return left / right; },
            py::return_value_policy::reference)  // NOLINT
        .def(
            "__truediv__",
            [](const Var &left, const int64_t &right) -> Expr & {
                return left / convert_int_to_const(left, right);
            },
            py::return_value_policy::reference)  // NOLINT
        .def(
            "__mul__",
            [](const int64_t &left, Var &right) -> Expr & {
                return convert_int_to_const(left, right) * right;
            },
            py::return_value_policy::reference)  // NOLINT
        .def(
            "__mod__", [](const Var &left, const Var &right) -> Expr & { return left % right; },
            py::return_value_policy::reference)  // NOLINT
        .def(
            "__mod__",
            [](const Var &left, const int64_t &right) -> Expr & {
                return left % convert_int_to_const(left, right);
            },
            py::return_value_policy::reference)  // NOLINT
        .def(
            "__mod__",
            [](const int64_t &left, Var &right) -> Expr & {
                return convert_int_to_const(left, right) % right;
            },
            py::return_value_policy::reference)  // NOLINT
        .def(
            "__div__", [](const Var &left, const Var &right) -> Expr & { return left / right; },
            py::return_value_policy::reference)  // NOLINT
        .def(
            "__div__",
            [](const Var &left, const int64_t &right) -> Expr & {
                return left / convert_int_to_const(left, right);
            },
            py::return_value_policy::reference)  // NOLINT
        .def(
            "__div__",
            [](const int64_t &left, Var &right) -> Expr & {
                return convert_int_to_const(left, right) / right;
            },
            py::return_value_policy::reference)  // NOLINT
        .def(
            "__rshift__", [](const Var &left, const Var &right) -> Expr & { return left >> right; },
            py::return_value_policy::reference)  // NOLINT
        .def(
            "__rshift__",
            [](const Var &left, const int64_t &right) -> Expr & {
                return left >> convert_int_to_const(left, right);
            },
            py::return_value_policy::reference)  // NOLINT
        .def(
            "__rshift__",
            [](const int64_t &left, Var &right) -> Expr & {
                return convert_int_to_const(left, right) >> right;
            },
            py::return_value_policy::reference)  // NOLINT
        .def(
            "__or__", [](const Var &left, const Var &right) -> Expr & { return left | right; },
            py::return_value_policy::reference)  // NOLINT
        .def(
            "__or__",
            [](const Var &left, const int64_t &right) -> Expr & {
                return left | convert_int_to_const(left, right);
            },
            py::return_value_policy::reference)  // NOLINT
        .def(
            "__or__",
            [](const int64_t &left, Var &right) -> Expr & {
                return convert_int_to_const(left, right) | right;
            },
            py::return_value_policy::reference)  // NOLINT
        .def(
            "__and__", [](const Var &left, const Var &right) -> Expr & { return left & right; },
            py::return_value_policy::reference)  // NOLINT
        .def(
            "__and__",
            [](const Var &left, const int64_t &right) -> Expr & {
                return left & convert_int_to_const(left, right);
            },
            py::return_value_policy::reference)  // NOLINT
        .def(
            "__and__",
            [](const int64_t &left, Var &right) -> Expr & {
                return convert_int_to_const(left, right) & right;
            },
            py::return_value_policy::reference)  // NOLINT
        .def(
            "__xor__", [](const Var &left, const Var &right) -> Expr & { return left ^ right; },
            py::return_value_policy::reference)  // NOLINT
        .def(
            "__xor__",
            [](const Var &left, const int64_t &right) -> Expr & {
                return left ^ convert_int_to_const(left, right);
            },
            py::return_value_policy::reference)  // NOLINT
        .def(
            "__xor__",
            [](const int64_t &left, Var &right) -> Expr & {
                return convert_int_to_const(left, right) ^ right;
            },
            py::return_value_policy::reference)                       // NOLINT
        .def("ashr", &Var::ashr, py::return_value_policy::reference)  // NOLINT
        .def(
            "ashr",
            [](const Var &left, const int64_t &right) -> Expr & {
                return left.ashr(convert_int_to_const(left, right));
            },
            py::return_value_policy::reference)  // NOLINT
        .def(
            "ashr",
            [](const int64_t &left, Var &right) -> Expr & {
                return convert_int_to_const(left, right).ashr(right);
            },
            py::return_value_policy::reference)  // NOLINT
        .def(
            "__lt__", [](const Var &left, const Var &right) -> Expr & { return left < right; },
            py::return_value_policy::reference)  // NOLINT
        .def(
            "__lt__",
            [](const Var &left, const int64_t &right) -> Expr & {
                return left < convert_int_to_const(left, right);
            },
            py::return_value_policy::reference)  // NOLINT
        .def(
            "__lt__",
            [](const int64_t &left, Var &right) -> Expr & {
                return convert_int_to_const(left, right) < right;
            },
            py::return_value_policy::reference)  // NOLINT
        .def(
            "__gt__", [](const Var &left, const Var &right) -> Expr & { return left > right; },
            py::return_value_policy::reference)  // NOLINT
        .def(
            "__gt__",
            [](const Var &left, const int64_t &right) -> Expr & {
                return left > convert_int_to_const(left, right);
            },
            py::return_value_policy::reference)  // NOLINT
        .def(
            "__gt__",
            [](const int64_t &left, Var &right) -> Expr & {
                return convert_int_to_const(left, right) > right;
            },
            py::return_value_policy::reference)  // NOLINT
        .def(
            "__le__", [](const Var &left, const Var &right) -> Expr & { return left <= right; },
            py::return_value_policy::reference)  // NOLINT
        .def(
            "__le__",
            [](const Var &left, const int64_t &right) -> Expr & {
                return left <= convert_int_to_const(left, right);
            },
            py::return_value_policy::reference)  // NOLINT
        .def(
            "__le__",
            [](const int64_t &left, Var &right) -> Expr & {
                return convert_int_to_const(left, right) <= right;
            },
            py::return_value_policy::reference)  // NOLINT
        .def(
            "__ge__", [](const Var &left, const Var &right) -> Expr & { return left >= right; },
            py::return_value_policy::reference)  // NOLINT
        .def(
            "__ge__",
            [](const Var &left, const int64_t &right) -> Expr & {
                return left >= convert_int_to_const(left, right);
            },
            py::return_value_policy::reference)  // NOLINT
        .def(
            "__ge__",
            [](const int64_t &left, Var &right) -> Expr & {
                return convert_int_to_const(left, right) >= right;
            },
            py::return_value_policy::reference)  // NOLINT
        .def("__eq__", &Var::eq, py::return_value_policy::reference)
        .def(
            "__eq__",
            [](const Var &left, const int64_t &right) -> Expr & {
                return left.eq(convert_int_to_const(left, right));
            },
            py::return_value_policy::reference)  // NOLINT
        .def(
            "__eq__",
            [](const int64_t &left, Var &right) -> Expr & {
                return convert_int_to_const(left, right).eq(right);
            },
            py::return_value_policy::reference)  // NOLINT
        .def("eq", &Var::eq, py::return_value_policy::reference)
        .def(
            "eq",
            [](const Var &left, const int64_t &right) -> Expr & {
                return left.eq(convert_int_to_const(left, right));
            },
            py::return_value_policy::reference)  // NOLINT
        .def(
            "eq",
            [](const int64_t &left, Var &right) -> Expr & {
                return convert_int_to_const(left, right).eq(right);
            },
            py::return_value_policy::reference)  // NOLINT
        .def(
            "__ne__", [](const Var &left, const Var &right) -> Expr & { return left != right; },
            py::return_value_policy::reference)  // NOLINT
        .def(
            "__ne__",
            [](const Var &left, const int64_t &right) -> Expr & {
                return left != convert_int_to_const(left, right);
            },
            py::return_value_policy::reference)  // NOLINT
        .def(
            "__neq__",
            [](const int64_t &left, Var &right) -> Expr & {
                return convert_int_to_const(left, right) != right;
            },
            py::return_value_policy::reference)
        .def("r_or", &Var::r_or, py::return_value_policy::reference)
        .def("r_xor", &Var::r_xor, py::return_value_policy::reference)
        .def("r_not", &Var::r_not, py::return_value_policy::reference)
        .def("r_and", &Var::r_and, py::return_value_policy::reference)
        .def("assign", py::overload_cast<const shared_ptr<Var> &>(&Var::assign),
             py::return_value_policy::reference)
        .def(
            "assign",
            [](Var &left, const int64_t right) -> std::shared_ptr<AssignStmt> {
                return left.assign(convert_int_to_const(left, right));
            },
            py::return_value_policy::reference)
        .def("assign", py::overload_cast<const shared_ptr<Var> &>(&Var::assign))
        .def("__call__",
             [](Var &left, const int64_t right) -> std::shared_ptr<AssignStmt> {
                 return left.assign(convert_int_to_const(left, right));
             })
        .def("__call__", py::overload_cast<const shared_ptr<Var> &>(&Var::assign))
        .def("type", &Var::type)
        .def("concat", &Var::concat, py::return_value_policy::reference)
        .def("extend", &Var::extend, py::return_value_policy::reference)
        .def_readwrite("name", &Var::name)
        .def_property(
            "width", [](Var &var) { return var.var_width(); },
            [](Var &var, uint32_t width) {
                var.var_width() = width;
                if (var.generator->debug) {
                    auto fn_ln = get_fn_ln(1);
                    if (fn_ln) {
                        var.fn_name_ln.emplace_back(*fn_ln);
                    }
                }
            })
        .def_property(
            "signed", [](Var &v) { return v.is_signed(); },
            [](Var &v, bool s) { v.is_signed() = s; })
        .def_property_readonly("size", [](const Var &var) { return var.size(); })
        .def_property("explicit_array", &Var::explicit_array, &Var::set_explicit_array)
        .def("sources", &Var::sources, py::return_value_policy::reference)
        .def("sinks", &Var::sinks, py::return_value_policy::reference)
        .def("cast", &Var::cast)
        .def_property("is_packed", &Var::is_packed, &Var::set_is_packed)
        .def_property_readonly(
            "generator", [](const Var &var) { return var.generator; },
            py::return_value_policy::reference)
        .def_static("move_src_to", &Var::move_src_to)
        .def_static("move_sink_to", &Var::move_sink_to)
        .def("handle_name", [](const Var &var) { return var.handle_name(); })
        .def("handle_name",
             [](const Var &var, bool ignore_top) { return var.handle_name(ignore_top); })
        .def("handle_name", [](const Var &var, Generator *gen) { return var.handle_name(gen); });

    def_attributes<py::class_<Var, ::shared_ptr<Var>>, Var>(class_);
}

void init_getitem(py::class_<kratos::Var, ::shared_ptr<kratos::Var>> &class_) {
    namespace py = pybind11;
    using namespace kratos;
    class_
        .def(
            "__getitem__", [](Var & k, std::pair<uint32_t, uint32_t> v) -> auto & { return k[v]; },
            py::return_value_policy::reference)
        .def(
            "__getitem__", [](Var & k, uint32_t idx) -> auto & { return k[idx]; },
            py::return_value_policy::reference)
        .def(
            "__getitem__",
            [](Var & k, const std::shared_ptr<Var> &var) -> auto & { return k[var]; },
            py::return_value_policy::reference);
}

// deal with all the expr/var stuff
void init_expr(py::module &m) {
    using namespace kratos;
    auto var = py::class_<Var, ::shared_ptr<Var>>(m, "Var");
    init_common_expr(var);
    init_getitem(var);
    def_trace<py::class_<Var, ::shared_ptr<Var>>, Var>(var);

    auto expr = py::class_<Expr, ::shared_ptr<Expr>, Var>(m, "Expr");

    auto port = py::class_<Port, ::shared_ptr<Port>, Var>(m, "Port");
    port.def_property_readonly("port_direction", &Port::port_direction)
        .def_property_readonly("port_type", &Port::port_type)
        .def_property("active_high", &Port::active_high, &Port::set_active_high);

    auto const_ = py::class_<Const, ::shared_ptr<Const>, Var>(m, "Const");
    const_.def("value", &Const::value).def("set_value", &Const::set_value);

    auto slice = py::class_<VarSlice, ::shared_ptr<VarSlice>, Var>(m, "VarSlice");
    slice.def_property_readonly("sliced_by_var", &VarSlice::sliced_by_var)
        .def_property_readonly("high", [](VarSlice &var) { return var.high; })
        .def_property_readonly("low", [](VarSlice &var) { return var.low; });

    auto var_slice = py::class_<VarVarSlice, ::shared_ptr<VarVarSlice>, VarSlice>(m, "VarVarSlice");
    var_slice.def_property_readonly(
        "slice_var", [](VarVarSlice &var) { return var.sliced_var(); },
        py::return_value_policy::reference);

    auto concat = py::class_<VarConcat, ::shared_ptr<VarConcat>, Var>(m, "VarConcat");

    auto param = py::class_<Param, ::shared_ptr<Param>, Var>(m, "Param");
    param.def_property("value", &Param::value, [](Param &param, const py::object &value) {
        // determine the type and cast
        try {
            auto v = value.cast<int64_t>();
            param.set_value(v);
        } catch (py::cast_error &) {
            // try with param instead
            // if it fail, a cast error will raise here
            auto v = value.cast<const std::shared_ptr<Param>>();
            param.set_value(v);
        }
        if (param.generator->debug) {
            // store the line change info
            auto info = get_fn_ln(1);
            if (info) {
                param.fn_name_ln.emplace_back(*info);
            }
        }
    });

    auto port_packed =
        py::class_<PortPackedStruct, ::shared_ptr<PortPackedStruct>, Var>(m, "PortPackedStruct");
    port_packed.def("port_direction", &PortPackedStruct::port_direction)
        .def("port_type", &PortPackedStruct::port_type)
        .def(
            "__getitem__",
            [](PortPackedStruct & port, const std::string &name) -> auto & { return port[name]; },
            py::return_value_policy::reference)
        .def("member_names", &PortPackedStruct::member_names);

    auto var_packed =
        py::class_<VarPackedStruct, ::shared_ptr<VarPackedStruct>, Var>(m, "VarPackedStruct");
    var_packed
        .def(
            "__getitem__",
            [](VarPackedStruct & port, const std::string &name) -> auto & { return port[name]; },
            py::return_value_policy::reference)
        .def("member_names", &VarPackedStruct::member_names);

    // struct info for packed
    auto struct_ = py::class_<PackedStruct>(m, "PackedStruct");
    struct_.def(py::init<std::string, std::vector<std::tuple<std::string, uint32_t, bool>>>())
        .def_readonly("struct_name", &PackedStruct::struct_name)
        .def_readonly("attributes", &PackedStruct::attributes);

    auto port_packed_slice =
        py::class_<PackedSlice, ::shared_ptr<PackedSlice>, Var>(m, "PackedSlice");

    // ternary op
    auto ternary_exp =
        py::class_<ConditionalExpr, ::shared_ptr<ConditionalExpr>, Expr>(m, "ConditionalExpr");
    ternary_exp.def(py::init<const std::shared_ptr<Var> &, const std::shared_ptr<Var> &,
                             const std::shared_ptr<Var> &>());
    // function call expr
    auto call_Var =
        py::class_<FunctionCallVar, ::shared_ptr<FunctionCallVar>, Var>(m, "FunctionCallVar");

    // constant
    m.def("constant", &constant, py::return_value_policy::reference);

    m.def("mux", util::mux);

    py::class_<EnumVar, ::shared_ptr<EnumVar>, Var>(m, "EnumVar")
        .def("enum_type", &EnumVar::enum_type);

    auto enum_const = py::class_<EnumConst, ::shared_ptr<EnumConst>, Var>(m, "EnumConst");

    auto var_extend = py::class_<VarExtend, ::shared_ptr<VarExtend>, Var>(m, "VarExtend");

    auto enum_port = py::class_<EnumPort, ::shared_ptr<EnumPort>, Port>(m, "EnumPort");

    py::class_<VarCasted, ::shared_ptr<VarCasted>, Var>(m, "VarCasted")
        .def_property("enum_type", &VarCasted::enum_type, &VarCasted::set_enum_type);
}

void init_enum_type(py::module &m) {
    using namespace kratos;
    auto enum_ = py::class_<Enum, std::shared_ptr<Enum>>(m, "Enum");
    enum_.def_readonly("name", &Enum::name)
        .def("__getitem__",
             [](Enum &enum_, const std::string &name) { return enum_.get_enum(name); })
        .def("__getattr__",
             [](Enum &enum_, const std::string &name) { return enum_.get_enum(name); });
}
