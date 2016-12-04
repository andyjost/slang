import numpy as np
import itertools
from slang.data import Cursor, Token
from slang.functors import *
from sklearn import preprocessing

STATEMENT_LIMIT = 3
LINE_LIMIT = 115

CURSOR_KINDS = [
  # , CursorKind.UNEXPOSED_DECL
    CursorKind.STRUCT_DECL
  # , UNION_DECL
  , CursorKind.CLASS_DECL
  # , CursorKind.ENUM_DECL
  # , CursorKind.FIELD_DECL
  # , CursorKind.ENUM_CONSTANT_DECL
  , CursorKind.FUNCTION_DECL
  # , CursorKind.VAR_DECL
  , CursorKind.PARM_DECL
  # , CursorKind.OBJC_INTERFACE_DECL
  # , CursorKind.OBJC_CATEGORY_DECL
  # , CursorKind.OBJC_PROTOCOL_DECL
  # , CursorKind.OBJC_PROPERTY_DECL
  # , CursorKind.OBJC_IVAR_DECL
  # , CursorKind.OBJC_INSTANCE_METHOD_DECL
  # , CursorKind.OBJC_CLASS_METHOD_DECL
  # , CursorKind.OBJC_IMPLEMENTATION_DECL
  # , CursorKind.OBJC_CATEGORY_IMPL_DECL
  # , CursorKind.TYPEDEF_DECL
  , CursorKind.CXX_METHOD
  , CursorKind.NAMESPACE
  , CursorKind.LINKAGE_SPEC
  , CursorKind.CONSTRUCTOR
  , CursorKind.DESTRUCTOR
  , CursorKind.CONVERSION_FUNCTION
  # , CursorKind.TEMPLATE_TYPE_PARAMETER
  # , CursorKind.TEMPLATE_NON_TYPE_PARAMETER
  # , CursorKind.TEMPLATE_TEMPLATE_PARAMETER
  , CursorKind.FUNCTION_TEMPLATE
  , CursorKind.CLASS_TEMPLATE
  # , CursorKind.CLASS_TEMPLATE_PARTIAL_SPECIALIZATION
  # , CursorKind.NAMESPACE_ALIAS
  # , CursorKind.USING_DIRECTIVE
  # , CursorKind.USING_DECLARATION
  # , CursorKind.TYPE_ALIAS_DECL
  # , CursorKind.OBJC_SYNTHESIZE_DECL
  # , CursorKind.OBJC_DYNAMIC_DECL
  , CursorKind.CXX_ACCESS_SPEC_DECL
  # , CursorKind.OBJC_SUPER_CLASS_REF
  # , CursorKind.OBJC_PROTOCOL_REF
  # , CursorKind.OBJC_CLASS_REF
  # , CursorKind.TYPE_REF
  # , CursorKind.CXX_BASE_SPECIFIER
  # , CursorKind.TEMPLATE_REF
  # , CursorKind.NAMESPACE_REF
  # , CursorKind.MEMBER_REF
  # , CursorKind.LABEL_REF
  # , CursorKind.OVERLOADED_DECL_REF
  # , CursorKind.VARIABLE_REF
  # , CursorKind.INVALID_FILE
  # , CursorKind.NO_DECL_FOUND
  # , CursorKind.NOT_IMPLEMENTED
  # , CursorKind.INVALID_CODE
  # , CursorKind.UNEXPOSED_EXPR
  # , CursorKind.DECL_REF_EXPR
  # , CursorKind.MEMBER_REF_EXPR
  # , CursorKind.CALL_EXPR
  # , CursorKind.OBJC_MESSAGE_EXPR
  # , CursorKind.BLOCK_EXPR
  # , CursorKind.INTEGER_LITERAL
  # , CursorKind.FLOATING_LITERAL
  # , CursorKind.IMAGINARY_LITERAL
  # , CursorKind.STRING_LITERAL
  # , CursorKind.CHARACTER_LITERAL
  # , CursorKind.PAREN_EXPR
  # , CursorKind.UNARY_OPERATOR
  # , CursorKind.ARRAY_SUBSCRIPT_EXPR
  # , CursorKind.BINARY_OPERATOR
  # , CursorKind.COMPOUND_ASSIGNMENT_OPERATOR
  # , CursorKind.CONDITIONAL_OPERATOR
  # , CursorKind.CSTYLE_CAST_EXPR
  # , CursorKind.COMPOUND_LITERAL_EXPR
  # , CursorKind.INIT_LIST_EXPR
  # , CursorKind.ADDR_LABEL_EXPR
  , CursorKind.StmtExpr
  # , CursorKind.GENERIC_SELECTION_EXPR
  # , CursorKind.GNU_NULL_EXPR
  # , CursorKind.CXX_STATIC_CAST_EXPR
  # , CursorKind.CXX_DYNAMIC_CAST_EXPR
  # , CursorKind.CXX_REINTERPRET_CAST_EXPR
  # , CursorKind.CXX_CONST_CAST_EXPR
  # , CursorKind.CXX_FUNCTIONAL_CAST_EXPR
  # , CursorKind.CXX_TYPEID_EXPR
  # , CursorKind.CXX_BOOL_LITERAL_EXPR
  # , CursorKind.CXX_NULL_PTR_LITERAL_EXPR
  , CursorKind.CXX_THIS_EXPR
  , CursorKind.CXX_THROW_EXPR
  , CursorKind.CXX_NEW_EXPR
  , CursorKind.CXX_DELETE_EXPR
  # , CursorKind.CXX_UNARY_EXPR
  # , CursorKind.OBJC_STRING_LITERAL
  # , CursorKind.OBJC_ENCODE_EXPR
  # , CursorKind.OBJC_SELECTOR_EXPR
  # , CursorKind.OBJC_PROTOCOL_EXPR
  # , CursorKind.OBJC_BRIDGE_CAST_EXPR
  # , CursorKind.PACK_EXPANSION_EXPR
  # , CursorKind.SIZE_OF_PACK_EXPR
  # , CursorKind.LAMBDA_EXPR
  # , CursorKind.OBJ_BOOL_LITERAL_EXPR
  # , CursorKind.OBJ_SELF_EXPR
  # , CursorKind.UNEXPOSED_STMT
  # , CursorKind.LABEL_STMT
  # , CursorKind.COMPOUND_STMT
  , CursorKind.CASE_STMT
  # , CursorKind.DEFAULT_STMT
  , CursorKind.IF_STMT
  , CursorKind.SWITCH_STMT
  , CursorKind.WHILE_STMT
  , CursorKind.DO_STMT
  , CursorKind.FOR_STMT
  , CursorKind.GOTO_STMT
  # , CursorKind.INDIRECT_GOTO_STMT
  , CursorKind.CONTINUE_STMT
  , CursorKind.BREAK_STMT
  , CursorKind.RETURN_STMT
  # , CursorKind.ASM_STMT
  # , CursorKind.OBJC_AT_TRY_STMT
  # , CursorKind.OBJC_AT_CATCH_STMT
  # , CursorKind.OBJC_AT_FINALLY_STMT
  # , CursorKind.OBJC_AT_THROW_STMT
  # , CursorKind.OBJC_AT_SYNCHRONIZED_STMT
  # , CursorKind.OBJC_AUTORELEASE_POOL_STMT
  # , CursorKind.OBJC_FOR_COLLECTION_STMT
  , CursorKind.CXX_CATCH_STMT
  , CursorKind.CXX_TRY_STMT
  # , CursorKind.CXX_FOR_RANGE_STMT
  # , CursorKind.SEH_TRY_STMT
  # , CursorKind.SEH_EXCEPT_STMT
  # , CursorKind.SEH_FINALLY_STMT
  # , CursorKind.MS_ASM_STMT
  # , CursorKind.NULL_STMT
  # , CursorKind.DECL_STMT
  , CursorKind.TRANSLATION_UNIT
  # , CursorKind.UNEXPOSED_ATTR
  # , CursorKind.IB_ACTION_ATTR
  # , CursorKind.IB_OUTLET_ATTR
  # , CursorKind.IB_OUTLET_COLLECTION_ATTR
  # , CursorKind.CXX_FINAL_ATTR
  # , CursorKind.CXX_OVERRIDE_ATTR
  # , CursorKind.ANNOTATE_ATTR
  # , CursorKind.ASM_LABEL_ATTR
  # , CursorKind.PACKED_ATTR
  # , CursorKind.PURE_ATTR
  # , CursorKind.CONST_ATTR
  # , CursorKind.NODUPLICATE_ATTR
  # , CursorKind.CUDACONSTANT_ATTR
  # , CursorKind.CUDADEVICE_ATTR
  # , CursorKind.CUDAGLOBAL_ATTR
  # , CursorKind.CUDAHOST_ATTR
  # , CursorKind.CUDASHARED_ATTR
  # , CursorKind.VISIBILITY_ATTR
  # , CursorKind.DLLEXPORT_ATTR
  # , CursorKind.DLLIMPORT_ATTR
  # , CursorKind.PREPROCESSING_DIRECTIVE
  # , CursorKind.MACRO_DEFINITION
  # , CursorKind.MACRO_INSTANTIATION
  # , CursorKind.INCLUSION_DIRECTIVE
  # , CursorKind.MODULE_IMPORT_DECL
  # , CursorKind.TYPE_ALIAS_TEMPLATE_DECL
  ]

KEYWORDS = [
  #   'alignas'
  # , 'alignof'
  # , 'and'
  # , 'and_eq'
  # , 'asm'
  # , 'atomic_cancel'
  # , 'atomic_commit'
  # , 'atomic_noexcept'
  # , 'auto'
  # , 'bitand'
  # , 'bitor'
  # , 'bool'
  # , 'break'
  # , 'case'
  # , 'catch'
  # , 'char'
  # , 'char16_t'
  # , 'char32_t'
    'class'
  # , 'compl'
  # , 'concept'
  # , 'const'
  # , 'constexpr'
  # , 'const_cast'
  # , 'continue'
  # , 'decltype'
  # , 'default'
  # , 'delete'
  # , 'do'
  # , 'double'
  # , 'dynamic_cast'
  # , 'else'
  # , 'enum'
  # , 'explicit'
  # , 'export'
  # , 'extern'
  # , 'false'
  # , 'float'
  , 'for'
  #, 'friend'
  #, 'goto'
  , 'if'
  #, 'import'
  , 'inline'
  #, 'int'
  #, 'long'
  #, 'module'
  #, 'mutable'
  # , 'namespace'
  #, 'new'
  # , 'noexcept'
  # , 'not'
  # , 'not_eq'
  # , 'nullptr'
  , 'operator'
  # , 'or'
  # , 'or_eq'
  # , 'private'
  # , 'protected'
  # , 'public'
  # , 'register'
  # , 'reinterpret_cast'
  # , 'requires'
  , 'return'
  # , 'short'
  # , 'signed'
  # , 'sizeof'
  , 'static'
  # , 'static_assert'
  # , 'static_cast'
  , 'struct'
  # , 'switch'
  # , 'synchronized'
  , 'template'
  , 'this'
  # , 'thread_local'
  , 'throw'
  # , 'true'
  , 'try'
  # , 'typedef'
  # , 'typeid'
  # , 'typename'
  # , 'union'
  # , 'unsigned'
  # , 'using'
  # , 'virtual'
  # , 'void'
  # , 'volatile'
  # , 'wchar_t'
  , 'while'
  # , 'xor'
  # , 'xor_eq'
  ]

LOGICAL = [not_, and_, or_]
COMPARISONS = [lt, gt, ge, le, eq, ne]
RELATIONS = [up, down, left, right]
PROPERTIES = [
    lt(function_body_stmts(_), STATEMENT_LIMIT)
  , lt(length_as_single_line(_), LINE_LIMIT)
  , is_whitespace
  , is_space
  , is_line_end
  ] \
  + [contains_keyword(_, kw) for kw in KEYWORDS] \
  + [ is_kind(_, kind) for kind in CURSOR_KINDS ] \
  + [ is_spelled(_, kw) for kw in KEYWORDS ]

def coinflip(p=0.5):
  return np.random.random() < p

choice = np.random.choice

class Gene(object):
  '''Produces a set of features based on a cursor or token object.'''
  def __init__(self, relation, props):
    self.relation = relation
    self.props = props
  @staticmethod
  def create(kwds):
    steps = choice(kwds.get('order'))
    relation = [ Gene._new_relation(kwds) for i in xrange(steps) ]
    props = Gene._new_property(kwds.get('n_props'))
    return Gene(relation, props)
  def __call__(self, obj):
    for r in self.relation:
      obj = r(obj)
    return np.array([prop(obj) for prop in self.props], dtype=object)
  def mutate(self, kwds):
    relation = self._mutate_relation(kwds) \
        if coinflip(kwds.get('p_rel_mutate')) else self.relation
    props = self._mutate_props(kwds)
    return Gene(relation, props)
  @staticmethod
  def _new_relation(kwds):
    r = choice(RELATIONS)
    if r is down:
      return down(_, choice(kwds.get('max_down_subscript')))
    return r
  def _mutate_relation(self, kwds):
    # template = choice(self.genes)
    l = len(self.relation)
    assert l <= kwds.get('order')
    #             [ ]   [ a ]   [ a,b ]
    # holes:       ^     ^ ^     ^ ^ ^
    # elements:           ^       ^ ^
    if l == 0:
      pos = 0
    elif l == kwds.get('order') or coinflip(kwds.get('p_rel_del')):
      pos = 2 * choice(l + 1)
    else:
      pos = 2 * choice(l) + 1
    rel = self.relation[:]
    if pos % 2 == 0:
      rel.insert(pos//2, Gene._new_relation(kwds))
    else:
      del rel[pos//2]
    return rel
  @staticmethod
  def _new_property(n=1):
    return [ choice(PROPERTIES) for i in xrange(n) ]
  def _mutate_props(self, kwds):
    old_props = self.props[:]
    new_props = []
    for i in xrange(choice(kwds.get('n_prop_mutate')) + 1):
      if old_props and coinflip(kwds.get('p_prop_del')):
        j = choice(len(old_props))
        del old_props[j]
      else:
        new_props += Gene._new_property()
    return old_props + new_props

# class Gene(object):
#   '''
#   Collects a set of cursor/token objects and associated properties.  Builds a
#   feature vector.
#   '''
#   def __init__(self, features):
#     # [relation,PropertyBundle]
#     # The first relations is always "this".
#     self.features = features
#   def __call__(self, obj):
#     return np.concatenate([bundle(rel(obj)) for rel,bundle in self.features])

class Genome(object):
  '''Represents a set of genes; produces feature vectors.'''
  kwds = {
      'order'              : 3     # max number of steps in relation
    , 'p_rel_del'          : 0.25  # delete a relation element
    , 'p_prop_del'         : 0.15  # delete a property
    , 'max_down_subscript' : 10    # max index when moving down
    , 'n_props'            : 5     # initial number of properties
    , 'p_rel_mutate'       : 0.05  # mutate the relation
    , 'n_prop_mutate'      : 2     # max number of property mutations
    }
  def __init__(self):
    self.genes = []
  def __call__(self, obj):
    return np.concatenate([gene(obj) for gene in self.genes])
  def mutate():
    # Add a new gene.
    # Select a gene and modify it.
    pass
  def cross(self, genome):
    pass
