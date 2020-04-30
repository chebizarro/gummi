<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:output method="text"/>
    <xsl:param name="rpath"/>

    <xsl:template match="/">
        <xsl:for-each select="gresources/gresource/file">
        <xsl:value-of select="$rpath"/><xsl:value-of select="text()"/><xsl:text>
        </xsl:text>
        </xsl:for-each>
    </xsl:template>

    <xsl:template match="text()" />

</xsl:stylesheet>