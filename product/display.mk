# Boot animation
TARGET_SCREEN_HEIGHT := 1280
TARGET_SCREEN_WIDTH := 720

# Screen density
PRODUCT_AAPT_CONFIG := normal
PRODUCT_AAPT_PREF_CONFIG := xxhdpi

# Default density
PRODUCT_DEFAULT_PROPERTY_OVERRIDES += \
		ro.sf.lcd_density=320

# Dalvik
$(call inherit-product, frameworks/native/build/phone-xxhdpi-2048-hwui-memory.mk)
