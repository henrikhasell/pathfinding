#ifndef TEXT_HPP
#define TEXT_HPP

void LoadCharacterTextures();
void FreeCharacterTextures();

void RenderString(const char string[]);
void RenderFormattedString(const char format[], ...);

#endif /* TEXT_HPP */
