package cf.jeanbisel.wipmod;

import javax.annotation.Nullable;
import net.minecraft.init.Biomes;
import net.minecraft.util.math.Vec3d;
import net.minecraft.world.biome.BiomeProviderSingle;
import net.minecraft.world.border.WorldBorder;
import net.minecraft.world.WorldProvider;
import net.minecraftforge.fml.relauncher.Side;
import net.minecraftforge.fml.relauncher.SideOnly;
import net.minecraft.world.DimensionType;
import cf.jeanbisel.wipmod.WIPBiome;
import net.minecraft.init.Biomes;

public class WorldProviderWIP extends WorldProvider
{
    /**
     * Creates a new {@link BiomeProvider} for the WorldProvider, and also sets the values of {@link #hasSkylight} and
     * {@link #hasNoSky} appropriately.
     *  
     * Note that subclasses generally override this method without calling the parent version.
     */

  public void init()
  {
		this.hasSkyLight = true;
        this.biomeProvider = new BiomeProviderSingle(cf.jeanbisel.wipmod.WIPMod.WIPbiome);

  }
  /**
   * Return Vec3D with biome specific fog color
   */
  @SideOnly(Side.CLIENT)
  public Vec3d getFogColor(float p_76562_1_, float p_76562_2_)
  {
	Vec3d original = super.getFogColor(p_76562_1_,p_76562_2_);
    return new Vec3d(original.z,original.z,original.y);
  }
  @SideOnly(Side.CLIENT)
  public Vec3d getSkyColor(net.minecraft.entity.Entity cameraEntity, float partialTicks)
  {
	Vec3d original = super.getSkyColor(cameraEntity, partialTicks);
    return new Vec3d(original.z,original.z,original.y);
  }


  @Override
  public DimensionType getDimensionType()
  {
      return DimensionType.byName("wipworld");
  }
}
