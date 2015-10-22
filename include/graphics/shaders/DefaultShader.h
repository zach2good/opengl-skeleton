/*

public String vertexShader = null;
public String fragmentShader = null;

public int numDirectionalLights = 2;
public int numPointLights = 8;
public int numSpotLights = 1;
public int numBones = 0;

public Config () 
{
}

public Config (final String vertexShader, final String fragmentShader) 
{
	this.vertexShader = vertexShader;
	this.fragmentShader = fragmentShader;
}

// Global uniforms
	public final int u_projTrans;
	public final int u_viewTrans;
	public final int u_projViewTrans;
	public final int u_cameraPosition;
	public final int u_cameraDirection;
	public final int u_cameraUp;
	public final int u_time;
	// Object uniforms
	public final int u_worldTrans;
	public final int u_viewWorldTrans;
	public final int u_projViewWorldTrans;
	public final int u_normalMatrix;
	public final int u_bones;
	// Material uniforms
	public final int u_shininess;
	public final int u_opacity;
	public final int u_diffuseColor;
	public final int u_diffuseTexture;
	public final int u_diffuseUVTransform;
	public final int u_specularColor;
	public final int u_specularTexture;
	public final int u_specularUVTransform;
	public final int u_emissiveColor;
	public final int u_emissiveTexture;
	public final int u_emissiveUVTransform;
	public final int u_reflectionColor;
	public final int u_reflectionTexture;
	public final int u_reflectionUVTransform;
	public final int u_normalTexture;
	public final int u_normalUVTransform;
	public final int u_ambientTexture;
	public final int u_ambientUVTransform;
	public final int u_alphaTest;
	// Lighting uniforms
	protected final int u_ambientCubemap;
	protected final int u_environmentCubemap;
	protected final int u_dirLights0color = register(new Uniform("u_dirLights[0].color"));
	protected final int u_dirLights0direction = register(new Uniform("u_dirLights[0].direction"));
	protected final int u_dirLights1color = register(new Uniform("u_dirLights[1].color"));
	protected final int u_pointLights0color = register(new Uniform("u_pointLights[0].color"));
	protected final int u_pointLights0position = register(new Uniform("u_pointLights[0].position"));
	protected final int u_pointLights0intensity = register(new Uniform("u_pointLights[0].intensity"));
	protected final int u_pointLights1color = register(new Uniform("u_pointLights[1].color"));
	protected final int u_spotLights0color = register(new Uniform("u_spotLights[0].color"));
	protected final int u_spotLights0position = register(new Uniform("u_spotLights[0].position"));
	protected final int u_spotLights0intensity = register(new Uniform("u_spotLights[0].intensity"));
	protected final int u_spotLights0direction = register(new Uniform("u_spotLights[0].direction"));
	protected final int u_spotLights0cutoffAngle = register(new Uniform("u_spotLights[0].cutoffAngle"));
	protected final int u_spotLights0exponent = register(new Uniform("u_spotLights[0].exponent"));
	protected final int u_spotLights1color = register(new Uniform("u_spotLights[1].color"));
	protected final int u_fogColor = register(new Uniform("u_fogColor"));
	protected final int u_shadowMapProjViewTrans = register(new Uniform("u_shadowMapProjViewTrans"));
	protected final int u_shadowTexture = register(new Uniform("u_shadowTexture"));
	protected final int u_shadowPCFOffset = register(new Uniform("u_shadowPCFOffset"));
	// FIXME Cache vertex attribute locations...

	protected int dirLightsLoc;
	protected int dirLightsColorOffset;
	protected int dirLightsDirectionOffset;
	protected int dirLightsSize;
	protected int pointLightsLoc;
	protected int pointLightsColorOffset;
	protected int pointLightsPositionOffset;
	protected int pointLightsIntensityOffset;
	protected int pointLightsSize;
	protected int spotLightsLoc;
	protected int spotLightsColorOffset;
	protected int spotLightsPositionOffset;
	protected int spotLightsDirectionOffset;
	protected int spotLightsIntensityOffset;
	protected int spotLightsCutoffAngleOffset;
	protected int spotLightsExponentOffset;
	protected int spotLightsSize;

	protected final boolean lighting;
	protected final boolean environmentCubemap;
	protected final boolean shadowMap;
	protected final AmbientCubemap ambientCubemap = new AmbientCubemap();
	protected final DirectionalLight directionalLights[];
	protected final PointLight pointLights[];
	protected final SpotLight spotLights[];


		this.directionalLights = new DirectionalLight[lighting && config.numDirectionalLights > 0 ? config.numDirectionalLights : 0];
		for (int i = 0; i < directionalLights.length; i++)
			directionalLights[i] = new DirectionalLight();
		this.pointLights = new PointLight[lighting && config.numPointLights > 0 ? config.numPointLights : 0];
		for (int i = 0; i < pointLights.length; i++)
			pointLights[i] = new PointLight();
		this.spotLights = new SpotLight[lighting && config.numSpotLights > 0 ? config.numSpotLights : 0];
		for (int i = 0; i < spotLights.length; i++)
			spotLights[i] = new SpotLight();

// Global uniforms
		u_projTrans = register(Inputs.projTrans, Setters.projTrans);
		u_viewTrans = register(Inputs.viewTrans, Setters.viewTrans);
		u_projViewTrans = register(Inputs.projViewTrans, Setters.projViewTrans);
		u_cameraPosition = register(Inputs.cameraPosition, Setters.cameraPosition);
		u_cameraDirection = register(Inputs.cameraDirection, Setters.cameraDirection);
		u_cameraUp = register(Inputs.cameraUp, Setters.cameraUp);
		u_time = register(new Uniform("u_time"));
		// Object uniforms
		u_worldTrans = register(Inputs.worldTrans, Setters.worldTrans);
		u_viewWorldTrans = register(Inputs.viewWorldTrans, Setters.viewWorldTrans);
		u_projViewWorldTrans = register(Inputs.projViewWorldTrans, Setters.projViewWorldTrans);
		u_normalMatrix = register(Inputs.normalMatrix, Setters.normalMatrix);
		u_bones = (renderable.bones != null && config.numBones > 0) ? register(Inputs.bones, new Setters.Bones(config.numBones))
			: -1;

		u_shininess = register(Inputs.shininess, Setters.shininess);
		u_opacity = register(Inputs.opacity);
		u_diffuseColor = register(Inputs.diffuseColor, Setters.diffuseColor);
		u_diffuseTexture = register(Inputs.diffuseTexture, Setters.diffuseTexture);
		u_diffuseUVTransform = register(Inputs.diffuseUVTransform, Setters.diffuseUVTransform);
		u_specularColor = register(Inputs.specularColor, Setters.specularColor);
		u_specularTexture = register(Inputs.specularTexture, Setters.specularTexture);
		u_specularUVTransform = register(Inputs.specularUVTransform, Setters.specularUVTransform);
		u_emissiveColor = register(Inputs.emissiveColor, Setters.emissiveColor);
		u_emissiveTexture = register(Inputs.emissiveTexture, Setters.emissiveTexture);
		u_emissiveUVTransform = register(Inputs.emissiveUVTransform, Setters.emissiveUVTransform);
		u_reflectionColor = register(Inputs.reflectionColor, Setters.reflectionColor);
		u_reflectionTexture = register(Inputs.reflectionTexture, Setters.reflectionTexture);
		u_reflectionUVTransform = register(Inputs.reflectionUVTransform, Setters.reflectionUVTransform);
		u_normalTexture = register(Inputs.normalTexture, Setters.normalTexture);
		u_normalUVTransform = register(Inputs.normalUVTransform, Setters.normalUVTransform);
		u_ambientTexture = register(Inputs.ambientTexture, Setters.ambientTexture);
		u_ambientUVTransform = register(Inputs.ambientUVTransform, Setters.ambientUVTransform);
		u_alphaTest = register(Inputs.alphaTest);

@Override
	public void init () {
		final ShaderProgram program = this.program;
		this.program = null;
		init(program, renderable);
		renderable = null;

		dirLightsLoc = loc(u_dirLights0color);
		dirLightsColorOffset = loc(u_dirLights0color) - dirLightsLoc;
		dirLightsDirectionOffset = loc(u_dirLights0direction) - dirLightsLoc;
		dirLightsSize = loc(u_dirLights1color) - dirLightsLoc;
		if (dirLightsSize < 0) dirLightsSize = 0;

		pointLightsLoc = loc(u_pointLights0color);
		pointLightsColorOffset = loc(u_pointLights0color) - pointLightsLoc;
		pointLightsPositionOffset = loc(u_pointLights0position) - pointLightsLoc;
		pointLightsIntensityOffset = has(u_pointLights0intensity) ? loc(u_pointLights0intensity) - pointLightsLoc : -1;
		pointLightsSize = loc(u_pointLights1color) - pointLightsLoc;
		if (pointLightsSize < 0) pointLightsSize = 0;

		spotLightsLoc = loc(u_spotLights0color);
		spotLightsColorOffset = loc(u_spotLights0color) - spotLightsLoc;
		spotLightsPositionOffset = loc(u_spotLights0position) - spotLightsLoc;
		spotLightsDirectionOffset = loc(u_spotLights0direction) - spotLightsLoc;
		spotLightsIntensityOffset = has(u_spotLights0intensity) ? loc(u_spotLights0intensity) - spotLightsLoc : -1;
		spotLightsCutoffAngleOffset = loc(u_spotLights0cutoffAngle) - spotLightsLoc;
		spotLightsExponentOffset = loc(u_spotLights0exponent) - spotLightsLoc;
		spotLightsSize = loc(u_spotLights1color) - spotLightsLoc;
		if (spotLightsSize < 0) spotLightsSize = 0;
	}

	public static String createPrefix (final Renderable renderable, final Config config) {
		final Attributes attributes = combineAttributes(renderable);
		String prefix = "";
		final long attributesMask = attributes.getMask();
		final long vertexMask = renderable.meshPart.mesh.getVertexAttributes().getMask();
		if (and(vertexMask, Usage.Position)) prefix += "#define positionFlag\n";
		if (or(vertexMask, Usage.ColorUnpacked | Usage.ColorPacked)) prefix += "#define colorFlag\n";
		if (and(vertexMask, Usage.BiNormal)) prefix += "#define binormalFlag\n";
		if (and(vertexMask, Usage.Tangent)) prefix += "#define tangentFlag\n";
		if (and(vertexMask, Usage.Normal)) prefix += "#define normalFlag\n";
		if (and(vertexMask, Usage.Normal) || and(vertexMask, Usage.Tangent | Usage.BiNormal)) {
			if (renderable.environment != null) {
				prefix += "#define lightingFlag\n";
				prefix += "#define ambientCubemapFlag\n";
				prefix += "#define numDirectionalLights " + config.numDirectionalLights + "\n";
				prefix += "#define numPointLights " + config.numPointLights + "\n";
				prefix += "#define numSpotLights " + config.numSpotLights + "\n";
				if (attributes.has(ColorAttribute.Fog)) {
					prefix += "#define fogFlag\n";
				}
				if (renderable.environment.shadowMap != null) prefix += "#define shadowMapFlag\n";
				if (attributes.has(CubemapAttribute.EnvironmentMap)) prefix += "#define environmentCubemapFlag\n";
			}
		}
		final int n = renderable.meshPart.mesh.getVertexAttributes().size();
		for (int i = 0; i < n; i++) {
			final VertexAttribute attr = renderable.meshPart.mesh.getVertexAttributes().get(i);
			if (attr.usage == Usage.BoneWeight)
				prefix += "#define boneWeight" + attr.unit + "Flag\n";
			else if (attr.usage == Usage.TextureCoordinates) prefix += "#define texCoord" + attr.unit + "Flag\n";
		}
		if ((attributesMask & BlendingAttribute.Type) == BlendingAttribute.Type)
			prefix += "#define " + BlendingAttribute.Alias + "Flag\n";
		if ((attributesMask & TextureAttribute.Diffuse) == TextureAttribute.Diffuse) {
			prefix += "#define " + TextureAttribute.DiffuseAlias + "Flag\n";
			prefix += "#define " + TextureAttribute.DiffuseAlias + "Coord texCoord0\n"; // FIXME implement UV mapping
		}
		if ((attributesMask & TextureAttribute.Specular) == TextureAttribute.Specular) {
			prefix += "#define " + TextureAttribute.SpecularAlias + "Flag\n";
			prefix += "#define " + TextureAttribute.SpecularAlias + "Coord texCoord0\n"; // FIXME implement UV mapping
		}
		if ((attributesMask & TextureAttribute.Normal) == TextureAttribute.Normal) {
			prefix += "#define " + TextureAttribute.NormalAlias + "Flag\n";
			prefix += "#define " + TextureAttribute.NormalAlias + "Coord texCoord0\n"; // FIXME implement UV mapping
		}
		if ((attributesMask & TextureAttribute.Emissive) == TextureAttribute.Emissive) {
			prefix += "#define " + TextureAttribute.EmissiveAlias + "Flag\n";
			prefix += "#define " + TextureAttribute.EmissiveAlias + "Coord texCoord0\n"; // FIXME implement UV mapping
		}
		if ((attributesMask & TextureAttribute.Reflection) == TextureAttribute.Reflection) {
			prefix += "#define " + TextureAttribute.ReflectionAlias + "Flag\n";
			prefix += "#define " + TextureAttribute.ReflectionAlias + "Coord texCoord0\n"; // FIXME implement UV mapping
		}
		if ((attributesMask & TextureAttribute.Ambient) == TextureAttribute.Ambient) {
			prefix += "#define " + TextureAttribute.AmbientAlias + "Flag\n";
			prefix += "#define " + TextureAttribute.AmbientAlias + "Coord texCoord0\n"; // FIXME implement UV mapping
		}
		if ((attributesMask & ColorAttribute.Diffuse) == ColorAttribute.Diffuse)
			prefix += "#define " + ColorAttribute.DiffuseAlias + "Flag\n";
		if ((attributesMask & ColorAttribute.Specular) == ColorAttribute.Specular)
			prefix += "#define " + ColorAttribute.SpecularAlias + "Flag\n";
		if ((attributesMask & ColorAttribute.Emissive) == ColorAttribute.Emissive)
			prefix += "#define " + ColorAttribute.EmissiveAlias + "Flag\n";
		if ((attributesMask & ColorAttribute.Reflection) == ColorAttribute.Reflection)
			prefix += "#define " + ColorAttribute.ReflectionAlias + "Flag\n";
		if ((attributesMask & FloatAttribute.Shininess) == FloatAttribute.Shininess)
			prefix += "#define " + FloatAttribute.ShininessAlias + "Flag\n";
		if ((attributesMask & FloatAttribute.AlphaTest) == FloatAttribute.AlphaTest)
			prefix += "#define " + FloatAttribute.AlphaTestAlias + "Flag\n";
		if (renderable.bones != null && config.numBones > 0) prefix += "#define numBones " + config.numBones + "\n";
		return prefix;
	}


@Override
	public void begin (final Camera camera, final RenderContext context) {
		super.begin(camera, context);

		for (final DirectionalLight dirLight : directionalLights)
			dirLight.set(0, 0, 0, 0, -1, 0);
		for (final PointLight pointLight : pointLights)
			pointLight.set(0, 0, 0, 0, 0, 0, 0);
		for (final SpotLight spotLight : spotLights)
			spotLight.set(0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 1, 0);
		lightsSet = false;

		if (has(u_time)) set(u_time, time += Gdx.graphics.getDeltaTime());
	}


@Override
	public void render (Renderable renderable, Attributes combinedAttributes) {
		if (!combinedAttributes.has(BlendingAttribute.Type))
			context.setBlending(false, GL20.GL_SRC_ALPHA, GL20.GL_ONE_MINUS_SRC_ALPHA);
		bindMaterial(combinedAttributes);
		if (lighting) bindLights(renderable, combinedAttributes);
		super.render(renderable, combinedAttributes);
	}

	@Override
	public void end () {
		super.end();
	}



	protected void bindMaterial (final Attributes attributes) {
		int cullFace = config.defaultCullFace == -1 ? defaultCullFace : config.defaultCullFace;
		int depthFunc = config.defaultDepthFunc == -1 ? defaultDepthFunc : config.defaultDepthFunc;
		float depthRangeNear = 0f;
		float depthRangeFar = 1f;
		boolean depthMask = true;

		for (final Attribute attr : attributes) {
			final long t = attr.type;
			if (BlendingAttribute.is(t)) {
				context.setBlending(true, ((BlendingAttribute)attr).sourceFunction, ((BlendingAttribute)attr).destFunction);
				set(u_opacity, ((BlendingAttribute)attr).opacity);
			} else if ((t & IntAttribute.CullFace) == IntAttribute.CullFace)
				cullFace = ((IntAttribute)attr).value;
			else if ((t & FloatAttribute.AlphaTest) == FloatAttribute.AlphaTest)
				set(u_alphaTest, ((FloatAttribute)attr).value);
			else if ((t & DepthTestAttribute.Type) == DepthTestAttribute.Type) {
				DepthTestAttribute dta = (DepthTestAttribute)attr;
				depthFunc = dta.depthFunc;
				depthRangeNear = dta.depthRangeNear;
				depthRangeFar = dta.depthRangeFar;
				depthMask = dta.depthMask;
			} else if (!config.ignoreUnimplemented) throw new GdxRuntimeException("Unknown material attribute: " + attr.toString());
		}

		context.setCullFace(cullFace);
		context.setDepthTest(depthFunc, depthRangeNear, depthRangeFar);
		context.setDepthMask(depthMask);
	}



	protected void bindLights (final Renderable renderable, final Attributes attributes) {
		final Environment lights = renderable.environment;
		final DirectionalLightsAttribute dla = attributes.get(DirectionalLightsAttribute.class, DirectionalLightsAttribute.Type);
		final Array<DirectionalLight> dirs = dla == null ? null : dla.lights;
		final PointLightsAttribute pla = attributes.get(PointLightsAttribute.class, PointLightsAttribute.Type);
		final Array<PointLight> points = pla == null ? null : pla.lights;
		final SpotLightsAttribute sla = attributes.get(SpotLightsAttribute.class, SpotLightsAttribute.Type);
		final Array<SpotLight> spots = sla == null ? null : sla.lights;

		if (dirLightsLoc >= 0) {
			for (int i = 0; i < directionalLights.length; i++) {
				if (dirs == null || i >= dirs.size) {
					if (lightsSet && directionalLights[i].color.r == 0f && directionalLights[i].color.g == 0f
						&& directionalLights[i].color.b == 0f) continue;
					directionalLights[i].color.set(0, 0, 0, 1);
				} else if (lightsSet && directionalLights[i].equals(dirs.get(i)))
					continue;
				else
					directionalLights[i].set(dirs.get(i));

				int idx = dirLightsLoc + i * dirLightsSize;
				program.setUniformf(idx + dirLightsColorOffset, directionalLights[i].color.r, directionalLights[i].color.g,
					directionalLights[i].color.b);
				program.setUniformf(idx + dirLightsDirectionOffset, directionalLights[i].direction.x,
					directionalLights[i].direction.y, directionalLights[i].direction.z);
				if (dirLightsSize <= 0) break;
			}
		}

		if (pointLightsLoc >= 0) {
			for (int i = 0; i < pointLights.length; i++) {
				if (points == null || i >= points.size) {
					if (lightsSet && pointLights[i].intensity == 0f) continue;
					pointLights[i].intensity = 0f;
				} else if (lightsSet && pointLights[i].equals(points.get(i)))
					continue;
				else
					pointLights[i].set(points.get(i));

				int idx = pointLightsLoc + i * pointLightsSize;
				program.setUniformf(idx + pointLightsColorOffset, pointLights[i].color.r * pointLights[i].intensity,
					pointLights[i].color.g * pointLights[i].intensity, pointLights[i].color.b * pointLights[i].intensity);
				program.setUniformf(idx + pointLightsPositionOffset, pointLights[i].position.x, pointLights[i].position.y,
					pointLights[i].position.z);
				if (pointLightsIntensityOffset >= 0) program.setUniformf(idx + pointLightsIntensityOffset, pointLights[i].intensity);
				if (pointLightsSize <= 0) break;
			}
		}

		if (spotLightsLoc >= 0) {
			for (int i = 0; i < spotLights.length; i++) {
				if (spots == null || i >= spots.size) {
					if (lightsSet && spotLights[i].intensity == 0f) continue;
					spotLights[i].intensity = 0f;
				} else if (lightsSet && spotLights[i].equals(spots.get(i)))
					continue;
				else
					spotLights[i].set(spots.get(i));

				int idx = spotLightsLoc + i * spotLightsSize;
				program.setUniformf(idx + spotLightsColorOffset, spotLights[i].color.r * spotLights[i].intensity,
					spotLights[i].color.g * spotLights[i].intensity, spotLights[i].color.b * spotLights[i].intensity);
				program.setUniformf(idx + spotLightsPositionOffset, spotLights[i].position);
				program.setUniformf(idx + spotLightsDirectionOffset, spotLights[i].direction);
				program.setUniformf(idx + spotLightsCutoffAngleOffset, spotLights[i].cutoffAngle);
				program.setUniformf(idx + spotLightsExponentOffset, spotLights[i].exponent);
				if (spotLightsIntensityOffset >= 0)
					program.setUniformf(idx + spotLightsIntensityOffset, spotLights[i].intensity);
				if (spotLightsSize <= 0) break;
			}
		}

		if (attributes.has(ColorAttribute.Fog)) {
			set(u_fogColor, ((ColorAttribute)attributes.get(ColorAttribute.Fog)).color);
		}

		if (lights != null && lights.shadowMap != null) {
			set(u_shadowMapProjViewTrans, lights.shadowMap.getProjViewTrans());
			set(u_shadowTexture, lights.shadowMap.getDepthMap());
			set(u_shadowPCFOffset, 1.f / (2f * lights.shadowMap.getDepthMap().texture.getWidth()));
		}

		lightsSet = true;
	}

	@Override
	public void dispose () {
		program.dispose();
		super.dispose();
	}

	public int getDefaultCullFace () {
		return config.defaultCullFace == -1 ? defaultCullFace : config.defaultCullFace;
	}

	public void setDefaultCullFace (int cullFace) {
		config.defaultCullFace = cullFace;
	}

	public int getDefaultDepthFunc () {
		return config.defaultDepthFunc == -1 ? defaultDepthFunc : config.defaultDepthFunc;
	}

	public void setDefaultDepthFunc (int depthFunc) {
		config.defaultDepthFunc = depthFunc;
	}


*/
