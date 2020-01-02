<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>
<%@ taglib uri="http://tiles.apache.org/tags-tiles" prefix="t" %>
<%@ page session="false" %>
<html>
<head>
    <title>Spitter</title>
    <link rel="stylesheet" type="text/css" href="<c:url value="/resources/style.css" />" />
</head>
<body>
    <div id="header">
        <t:insertAttribute name="header" />
    </div>
    <div id="body">
        <t:insertAttribute name="body" />
    </div>
    <div id="footer">
        <t:insertAttribute name="footer" />
    </div>
</body>
</html>
