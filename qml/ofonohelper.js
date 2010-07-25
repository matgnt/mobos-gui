function getCallerNumber(id) {
    console.log("ofonohelper.js: " + id);
    return OfonoContext.getPhoneNumber(id);
}
