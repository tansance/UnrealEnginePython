#include "UnrealEnginePythonPrivatePCH.h"

#if WITH_EDITOR

#include "UePyFbx.h"

static PyObject *py_ue_fbx_property_get_name(ue_PyFbxProperty *self, PyObject *args) {
	return PyUnicode_FromString(self->fbx_property.GetName());
}

static PyMethodDef ue_PyFbxProperty_methods[] = {
	{ "get_name", (PyCFunction)py_ue_fbx_property_get_name, METH_VARARGS, "" },
	{ NULL }  /* Sentinel */
};

static PyTypeObject ue_PyFbxPropertyType = {
	PyVarObject_HEAD_INIT(NULL, 0)
	"unreal_engine.FbxProperty", /* tp_name */
	sizeof(ue_PyFbxProperty),    /* tp_basicsize */
	0,                         /* tp_itemsize */
	0,   /* tp_dealloc */
	0,                         /* tp_print */
	0,                         /* tp_getattr */
	0,                         /* tp_setattr */
	0,                         /* tp_reserved */
	0,                         /* tp_repr */
	0,                         /* tp_as_number */
	0,                         /* tp_as_sequence */
	0,                         /* tp_as_mapping */
	0,                         /* tp_hash  */
	0,                         /* tp_call */
	0,                         /* tp_str */
	0,                         /* tp_getattro */
	0,                         /* tp_setattro */
	0,                         /* tp_as_buffer */
	Py_TPFLAGS_DEFAULT,        /* tp_flags */
	"Unreal Engine FbxProperty", /* tp_doc */
	0,                         /* tp_traverse */
	0,                         /* tp_clear */
	0,                         /* tp_richcompare */
	0,                         /* tp_weaklistoffset */
	0,                         /* tp_iter */
	0,                         /* tp_iternext */
	ue_PyFbxProperty_methods,    /* tp_methods */
	0,   /* tp_members */
	0,                         /* tp_getset */
};

static int py_ue_fbx_property_init(ue_PyFbxProperty *self, PyObject * args) {
	PyErr_SetString(PyExc_Exception, "instantiating a new FbxProperty is currently not supported");
	return -1;
}

void ue_python_init_fbx_property(PyObject *ue_module) {
	ue_PyFbxPropertyType.tp_new = PyType_GenericNew;;
	ue_PyFbxPropertyType.tp_init = (initproc)py_ue_fbx_property_init;
	if (PyType_Ready(&ue_PyFbxPropertyType) < 0)
		return;

	Py_INCREF(&ue_PyFbxPropertyType);
	PyModule_AddObject(ue_module, "FbxProperty", (PyObject *)&ue_PyFbxPropertyType);
}

PyObject *py_ue_new_fbx_property(FbxProperty fbx_property) {
	ue_PyFbxProperty *ret = (ue_PyFbxProperty *)PyObject_New(ue_PyFbxProperty, &ue_PyFbxPropertyType);
	ret->fbx_property = fbx_property;
	return (PyObject *)ret;
}

ue_PyFbxProperty *py_ue_is_fbx_property(PyObject *obj) {
	if (!PyObject_IsInstance(obj, (PyObject *)&ue_PyFbxPropertyType))
		return nullptr;
	return (ue_PyFbxProperty *)obj;
}
#endif